#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct udf_inode_info {scalar_t__ i_alloc_type; scalar_t__ i_lenExtents; int i_lenAlloc; int /*<<< orphan*/  i_location; } ;
struct short_ad {int dummy; } ;
struct long_ad {int dummy; } ;
struct kernel_lb_addr {int dummy; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_sb; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct extent_position {int offset; TYPE_2__* bh; int /*<<< orphan*/  block; TYPE_1__ member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct allocExtDesc {int /*<<< orphan*/  lengthAllocDescs; } ;
typedef  int int8_t ;
struct TYPE_7__ {int s_udfrev; } ;
struct TYPE_6__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int EXT_NOT_RECORDED_ALLOCATED ; 
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 scalar_t__ ICBTAG_FLAG_AD_LONG ; 
 scalar_t__ ICBTAG_FLAG_AD_SHORT ; 
 int /*<<< orphan*/  UDF_FLAG_STRICT ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  UDF_QUERY_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* UDF_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (TYPE_2__*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  extent_trunc (struct inode*,struct extent_position*,struct kernel_lb_addr*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (TYPE_2__*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int udf_file_entry_alloc_offset (struct inode*) ; 
 int udf_next_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,scalar_t__*,int) ; 
 int /*<<< orphan*/  udf_update_tag (scalar_t__,int) ; 

void udf_discard_prealloc(struct inode *inode)
{
	struct extent_position epos = { NULL, 0, {0, 0} };
	struct kernel_lb_addr eloc;
	uint32_t elen;
	uint64_t lbcount = 0;
	int8_t etype = -1, netype;
	int adsize;
	struct udf_inode_info *iinfo = UDF_I(inode);

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB ||
	    inode->i_size == iinfo->i_lenExtents)
		return;

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = sizeof(struct short_ad);
	else if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = sizeof(struct long_ad);
	else
		adsize = 0;

	epos.block = iinfo->i_location;

	/* Find the last extent in the file */
	while ((netype = udf_next_aext(inode, &epos, &eloc, &elen, 1)) != -1) {
		etype = netype;
		lbcount += elen;
	}
	if (etype == (EXT_NOT_RECORDED_ALLOCATED >> 30)) {
		epos.offset -= adsize;
		lbcount -= elen;
		extent_trunc(inode, &epos, &eloc, etype, elen, 0);
		if (!epos.bh) {
			iinfo->i_lenAlloc =
				epos.offset -
				udf_file_entry_alloc_offset(inode);
			mark_inode_dirty(inode);
		} else {
			struct allocExtDesc *aed =
				(struct allocExtDesc *)(epos.bh->b_data);
			aed->lengthAllocDescs =
				cpu_to_le32(epos.offset -
					    sizeof(struct allocExtDesc));
			if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
			    UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
				udf_update_tag(epos.bh->b_data, epos.offset);
			else
				udf_update_tag(epos.bh->b_data,
					       sizeof(struct allocExtDesc));
			mark_buffer_dirty_inode(epos.bh, inode);
		}
	}
	/* This inode entry is in-memory only and thus we don't have to mark
	 * the inode dirty */
	iinfo->i_lenExtents = lbcount;
	brelse(epos.bh);
}