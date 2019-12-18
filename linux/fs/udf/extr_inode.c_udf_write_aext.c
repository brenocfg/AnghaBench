#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_data; } ;
struct udf_inode_info {int i_alloc_type; int /*<<< orphan*/ * i_lenEAttr; TYPE_1__ i_ext; } ;
struct short_ad {void* extPosition; void* extLength; } ;
struct long_ad {int /*<<< orphan*/  impUse; int /*<<< orphan*/  extLocation; void* extLength; } ;
struct kernel_lb_addr {int /*<<< orphan*/  logicalBlockNum; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct extent_position {int offset; TYPE_2__* bh; } ;
struct allocExtDesc {int /*<<< orphan*/  lengthAllocDescs; } ;
struct TYPE_6__ {int s_udfrev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * b_data; } ;

/* Variables and functions */
#define  ICBTAG_FLAG_AD_LONG 129 
#define  ICBTAG_FLAG_AD_SHORT 128 
 int /*<<< orphan*/  UDF_FLAG_STRICT ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  UDF_QUERY_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* UDF_SB (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_lelb (struct kernel_lb_addr) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (TYPE_2__*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udf_file_entry_alloc_offset (struct inode*) ; 
 int /*<<< orphan*/  udf_update_tag (int /*<<< orphan*/ *,scalar_t__) ; 

void udf_write_aext(struct inode *inode, struct extent_position *epos,
		    struct kernel_lb_addr *eloc, uint32_t elen, int inc)
{
	int adsize;
	uint8_t *ptr;
	struct short_ad *sad;
	struct long_ad *lad;
	struct udf_inode_info *iinfo = UDF_I(inode);

	if (!epos->bh)
		ptr = iinfo->i_ext.i_data + epos->offset -
			udf_file_entry_alloc_offset(inode) +
			iinfo->i_lenEAttr;
	else
		ptr = epos->bh->b_data + epos->offset;

	switch (iinfo->i_alloc_type) {
	case ICBTAG_FLAG_AD_SHORT:
		sad = (struct short_ad *)ptr;
		sad->extLength = cpu_to_le32(elen);
		sad->extPosition = cpu_to_le32(eloc->logicalBlockNum);
		adsize = sizeof(struct short_ad);
		break;
	case ICBTAG_FLAG_AD_LONG:
		lad = (struct long_ad *)ptr;
		lad->extLength = cpu_to_le32(elen);
		lad->extLocation = cpu_to_lelb(*eloc);
		memset(lad->impUse, 0x00, sizeof(lad->impUse));
		adsize = sizeof(struct long_ad);
		break;
	default:
		return;
	}

	if (epos->bh) {
		if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
		    UDF_SB(inode->i_sb)->s_udfrev >= 0x0201) {
			struct allocExtDesc *aed =
				(struct allocExtDesc *)epos->bh->b_data;
			udf_update_tag(epos->bh->b_data,
				       le32_to_cpu(aed->lengthAllocDescs) +
				       sizeof(struct allocExtDesc));
		}
		mark_buffer_dirty_inode(epos->bh, inode);
	} else {
		mark_inode_dirty(inode);
	}

	if (inc)
		epos->offset += adsize;
}