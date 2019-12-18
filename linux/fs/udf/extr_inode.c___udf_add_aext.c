#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct udf_inode_info {scalar_t__ i_alloc_type; scalar_t__ i_lenAlloc; } ;
struct short_ad {int dummy; } ;
struct long_ad {int dummy; } ;
struct kernel_lb_addr {int dummy; } ;
struct inode {TYPE_3__* i_sb; } ;
struct extent_position {int offset; TYPE_1__* bh; } ;
struct allocExtDesc {int /*<<< orphan*/  lengthAllocDescs; } ;
struct TYPE_7__ {int s_blocksize; } ;
struct TYPE_6__ {int s_udfrev; } ;
struct TYPE_5__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ ICBTAG_FLAG_AD_LONG ; 
 scalar_t__ ICBTAG_FLAG_AD_SHORT ; 
 int /*<<< orphan*/  UDF_FLAG_STRICT ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  UDF_QUERY_FLAG (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* UDF_SB (TYPE_3__*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (TYPE_1__*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 scalar_t__ udf_file_entry_alloc_offset (struct inode*) ; 
 int /*<<< orphan*/  udf_update_tag (scalar_t__,int) ; 
 int /*<<< orphan*/  udf_write_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int /*<<< orphan*/ ,int) ; 

int __udf_add_aext(struct inode *inode, struct extent_position *epos,
		   struct kernel_lb_addr *eloc, uint32_t elen, int inc)
{
	struct udf_inode_info *iinfo = UDF_I(inode);
	struct allocExtDesc *aed;
	int adsize;

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = sizeof(struct short_ad);
	else if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = sizeof(struct long_ad);
	else
		return -EIO;

	if (!epos->bh) {
		WARN_ON(iinfo->i_lenAlloc !=
			epos->offset - udf_file_entry_alloc_offset(inode));
	} else {
		aed = (struct allocExtDesc *)epos->bh->b_data;
		WARN_ON(le32_to_cpu(aed->lengthAllocDescs) !=
			epos->offset - sizeof(struct allocExtDesc));
		WARN_ON(epos->offset + adsize > inode->i_sb->s_blocksize);
	}

	udf_write_aext(inode, epos, eloc, elen, inc);

	if (!epos->bh) {
		iinfo->i_lenAlloc += adsize;
		mark_inode_dirty(inode);
	} else {
		aed = (struct allocExtDesc *)epos->bh->b_data;
		le32_add_cpu(&aed->lengthAllocDescs, adsize);
		if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
				UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
			udf_update_tag(epos->bh->b_data,
					epos->offset + (inc ? 0 : adsize));
		else
			udf_update_tag(epos->bh->b_data,
					sizeof(struct allocExtDesc));
		mark_buffer_dirty_inode(epos->bh, inode);
	}

	return 0;
}