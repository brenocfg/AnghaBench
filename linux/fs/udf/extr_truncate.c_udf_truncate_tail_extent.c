#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct udf_inode_info {scalar_t__ i_alloc_type; scalar_t__ i_lenExtents; } ;
struct short_ad {int dummy; } ;
struct long_ad {int dummy; } ;
struct kernel_lb_addr {scalar_t__ logicalBlockNum; } ;
struct inode {scalar_t__ i_size; scalar_t__ i_nlink; scalar_t__ i_ino; TYPE_1__* i_sb; } ;
struct extent_position {int offset; int /*<<< orphan*/  bh; } ;
typedef  int int8_t ;
struct TYPE_3__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 scalar_t__ ICBTAG_FLAG_AD_LONG ; 
 scalar_t__ ICBTAG_FLAG_AD_SHORT ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_trunc (struct inode*,struct extent_position*,struct kernel_lb_addr*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udf_err (TYPE_1__*,char*,unsigned int) ; 
 int udf_next_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,scalar_t__*,int) ; 
 int /*<<< orphan*/  udf_warn (TYPE_1__*,char*,unsigned int,long long,long long,unsigned int,unsigned int) ; 

void udf_truncate_tail_extent(struct inode *inode)
{
	struct extent_position epos = {};
	struct kernel_lb_addr eloc;
	uint32_t elen, nelen;
	uint64_t lbcount = 0;
	int8_t etype = -1, netype;
	int adsize;
	struct udf_inode_info *iinfo = UDF_I(inode);

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB ||
	    inode->i_size == iinfo->i_lenExtents)
		return;
	/* Are we going to delete the file anyway? */
	if (inode->i_nlink == 0)
		return;

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = sizeof(struct short_ad);
	else if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = sizeof(struct long_ad);
	else
		BUG();

	/* Find the last extent in the file */
	while ((netype = udf_next_aext(inode, &epos, &eloc, &elen, 1)) != -1) {
		etype = netype;
		lbcount += elen;
		if (lbcount > inode->i_size) {
			if (lbcount - inode->i_size >= inode->i_sb->s_blocksize)
				udf_warn(inode->i_sb,
					 "Too long extent after EOF in inode %u: i_size: %lld lbcount: %lld extent %u+%u\n",
					 (unsigned)inode->i_ino,
					 (long long)inode->i_size,
					 (long long)lbcount,
					 (unsigned)eloc.logicalBlockNum,
					 (unsigned)elen);
			nelen = elen - (lbcount - inode->i_size);
			epos.offset -= adsize;
			extent_trunc(inode, &epos, &eloc, etype, elen, nelen);
			epos.offset += adsize;
			if (udf_next_aext(inode, &epos, &eloc, &elen, 1) != -1)
				udf_err(inode->i_sb,
					"Extent after EOF in inode %u\n",
					(unsigned)inode->i_ino);
			break;
		}
	}
	/* This inode entry is in-memory only and thus we don't have to mark
	 * the inode dirty */
	iinfo->i_lenExtents = inode->i_size;
	brelse(epos.bh);
}