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
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  partitionReferenceNum; } ;
struct TYPE_4__ {void* i_data; } ;
struct udf_inode_info {int i_lenAlloc; int i_alloc_type; TYPE_3__ i_location; int /*<<< orphan*/ * i_lenEAttr; TYPE_1__ i_ext; } ;
struct short_ad {int /*<<< orphan*/  extLength; int /*<<< orphan*/  extPosition; } ;
struct long_ad {int /*<<< orphan*/  extLength; int /*<<< orphan*/  extLocation; } ;
struct kernel_lb_addr {int logicalBlockNum; int /*<<< orphan*/  partitionReferenceNum; } ;
struct inode {int dummy; } ;
struct extent_position {int offset; TYPE_2__* bh; } ;
struct allocExtDesc {int /*<<< orphan*/  lengthAllocDescs; } ;
typedef  int int8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * b_data; } ;

/* Variables and functions */
#define  ICBTAG_FLAG_AD_LONG 129 
#define  ICBTAG_FLAG_AD_SHORT 128 
 int UDF_EXTENT_LENGTH_MASK ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct kernel_lb_addr lelb_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_debug (char*,int) ; 
 void* udf_file_entry_alloc_offset (struct inode*) ; 
 struct long_ad* udf_get_filelongad (int /*<<< orphan*/ *,int,int*,int) ; 
 struct short_ad* udf_get_fileshortad (int /*<<< orphan*/ *,int,int*,int) ; 

int8_t udf_current_aext(struct inode *inode, struct extent_position *epos,
			struct kernel_lb_addr *eloc, uint32_t *elen, int inc)
{
	int alen;
	int8_t etype;
	uint8_t *ptr;
	struct short_ad *sad;
	struct long_ad *lad;
	struct udf_inode_info *iinfo = UDF_I(inode);

	if (!epos->bh) {
		if (!epos->offset)
			epos->offset = udf_file_entry_alloc_offset(inode);
		ptr = iinfo->i_ext.i_data + epos->offset -
			udf_file_entry_alloc_offset(inode) +
			iinfo->i_lenEAttr;
		alen = udf_file_entry_alloc_offset(inode) +
							iinfo->i_lenAlloc;
	} else {
		if (!epos->offset)
			epos->offset = sizeof(struct allocExtDesc);
		ptr = epos->bh->b_data + epos->offset;
		alen = sizeof(struct allocExtDesc) +
			le32_to_cpu(((struct allocExtDesc *)epos->bh->b_data)->
							lengthAllocDescs);
	}

	switch (iinfo->i_alloc_type) {
	case ICBTAG_FLAG_AD_SHORT:
		sad = udf_get_fileshortad(ptr, alen, &epos->offset, inc);
		if (!sad)
			return -1;
		etype = le32_to_cpu(sad->extLength) >> 30;
		eloc->logicalBlockNum = le32_to_cpu(sad->extPosition);
		eloc->partitionReferenceNum =
				iinfo->i_location.partitionReferenceNum;
		*elen = le32_to_cpu(sad->extLength) & UDF_EXTENT_LENGTH_MASK;
		break;
	case ICBTAG_FLAG_AD_LONG:
		lad = udf_get_filelongad(ptr, alen, &epos->offset, inc);
		if (!lad)
			return -1;
		etype = le32_to_cpu(lad->extLength) >> 30;
		*eloc = lelb_to_cpu(lad->extLocation);
		*elen = le32_to_cpu(lad->extLength) & UDF_EXTENT_LENGTH_MASK;
		break;
	default:
		udf_debug("alloc_type = %u unsupported\n", iinfo->i_alloc_type);
		return -1;
	}

	return etype;
}