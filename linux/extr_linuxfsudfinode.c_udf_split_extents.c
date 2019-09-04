#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ udf_pblk_t ;
struct TYPE_7__ {scalar_t__ logicalBlockNum; scalar_t__ partitionReferenceNum; } ;
struct kernel_long_ad {int extLength; TYPE_3__ extLocation; } ;
struct inode {TYPE_2__* i_sb; } ;
typedef  int int8_t ;
struct TYPE_5__ {scalar_t__ partitionReferenceNum; } ;
struct TYPE_8__ {TYPE_1__ i_location; } ;
struct TYPE_6__ {unsigned long s_blocksize; unsigned char s_blocksize_bits; } ;

/* Variables and functions */
 int EXT_NOT_RECORDED_ALLOCATED ; 
 int EXT_NOT_RECORDED_NOT_ALLOCATED ; 
 unsigned long EXT_RECORDED_ALLOCATED ; 
 unsigned long UDF_EXTENT_LENGTH_MASK ; 
 TYPE_4__* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  udf_free_blocks (TYPE_2__*,struct inode*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void udf_split_extents(struct inode *inode, int *c, int offset,
			       udf_pblk_t newblocknum,
			       struct kernel_long_ad *laarr, int *endnum)
{
	unsigned long blocksize = inode->i_sb->s_blocksize;
	unsigned char blocksize_bits = inode->i_sb->s_blocksize_bits;

	if ((laarr[*c].extLength >> 30) == (EXT_NOT_RECORDED_ALLOCATED >> 30) ||
	    (laarr[*c].extLength >> 30) ==
				(EXT_NOT_RECORDED_NOT_ALLOCATED >> 30)) {
		int curr = *c;
		int blen = ((laarr[curr].extLength & UDF_EXTENT_LENGTH_MASK) +
			    blocksize - 1) >> blocksize_bits;
		int8_t etype = (laarr[curr].extLength >> 30);

		if (blen == 1)
			;
		else if (!offset || blen == offset + 1) {
			laarr[curr + 2] = laarr[curr + 1];
			laarr[curr + 1] = laarr[curr];
		} else {
			laarr[curr + 3] = laarr[curr + 1];
			laarr[curr + 2] = laarr[curr + 1] = laarr[curr];
		}

		if (offset) {
			if (etype == (EXT_NOT_RECORDED_ALLOCATED >> 30)) {
				udf_free_blocks(inode->i_sb, inode,
						&laarr[curr].extLocation,
						0, offset);
				laarr[curr].extLength =
					EXT_NOT_RECORDED_NOT_ALLOCATED |
					(offset << blocksize_bits);
				laarr[curr].extLocation.logicalBlockNum = 0;
				laarr[curr].extLocation.
						partitionReferenceNum = 0;
			} else
				laarr[curr].extLength = (etype << 30) |
					(offset << blocksize_bits);
			curr++;
			(*c)++;
			(*endnum)++;
		}

		laarr[curr].extLocation.logicalBlockNum = newblocknum;
		if (etype == (EXT_NOT_RECORDED_NOT_ALLOCATED >> 30))
			laarr[curr].extLocation.partitionReferenceNum =
				UDF_I(inode)->i_location.partitionReferenceNum;
		laarr[curr].extLength = EXT_RECORDED_ALLOCATED |
			blocksize;
		curr++;

		if (blen != offset + 1) {
			if (etype == (EXT_NOT_RECORDED_ALLOCATED >> 30))
				laarr[curr].extLocation.logicalBlockNum +=
								offset + 1;
			laarr[curr].extLength = (etype << 30) |
				((blen - (offset + 1)) << blocksize_bits);
			curr++;
			(*endnum)++;
		}
	}
}