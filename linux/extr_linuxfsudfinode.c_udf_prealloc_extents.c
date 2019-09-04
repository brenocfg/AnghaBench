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
struct long_ad {int dummy; } ;
struct TYPE_4__ {int logicalBlockNum; int /*<<< orphan*/  partitionReferenceNum; } ;
struct kernel_long_ad {int extLength; TYPE_1__ extLocation; } ;
struct inode {TYPE_2__* i_sb; } ;
struct TYPE_6__ {int i_lenExtents; } ;
struct TYPE_5__ {int s_blocksize; int s_blocksize_bits; } ;

/* Variables and functions */
 int EXT_NOT_RECORDED_ALLOCATED ; 
 int EXT_NOT_RECORDED_NOT_ALLOCATED ; 
 int UDF_DEFAULT_PREALLOC_BLOCKS ; 
 int UDF_EXTENT_LENGTH_MASK ; 
 TYPE_3__* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  memmove (struct kernel_long_ad*,struct kernel_long_ad*,int) ; 
 int udf_prealloc_blocks (TYPE_2__*,struct inode*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void udf_prealloc_extents(struct inode *inode, int c, int lastblock,
				 struct kernel_long_ad *laarr,
				 int *endnum)
{
	int start, length = 0, currlength = 0, i;

	if (*endnum >= (c + 1)) {
		if (!lastblock)
			return;
		else
			start = c;
	} else {
		if ((laarr[c + 1].extLength >> 30) ==
					(EXT_NOT_RECORDED_ALLOCATED >> 30)) {
			start = c + 1;
			length = currlength =
				(((laarr[c + 1].extLength &
					UDF_EXTENT_LENGTH_MASK) +
				inode->i_sb->s_blocksize - 1) >>
				inode->i_sb->s_blocksize_bits);
		} else
			start = c;
	}

	for (i = start + 1; i <= *endnum; i++) {
		if (i == *endnum) {
			if (lastblock)
				length += UDF_DEFAULT_PREALLOC_BLOCKS;
		} else if ((laarr[i].extLength >> 30) ==
				(EXT_NOT_RECORDED_NOT_ALLOCATED >> 30)) {
			length += (((laarr[i].extLength &
						UDF_EXTENT_LENGTH_MASK) +
				    inode->i_sb->s_blocksize - 1) >>
				    inode->i_sb->s_blocksize_bits);
		} else
			break;
	}

	if (length) {
		int next = laarr[start].extLocation.logicalBlockNum +
			(((laarr[start].extLength & UDF_EXTENT_LENGTH_MASK) +
			  inode->i_sb->s_blocksize - 1) >>
			  inode->i_sb->s_blocksize_bits);
		int numalloc = udf_prealloc_blocks(inode->i_sb, inode,
				laarr[start].extLocation.partitionReferenceNum,
				next, (UDF_DEFAULT_PREALLOC_BLOCKS > length ?
				length : UDF_DEFAULT_PREALLOC_BLOCKS) -
				currlength);
		if (numalloc) 	{
			if (start == (c + 1))
				laarr[start].extLength +=
					(numalloc <<
					 inode->i_sb->s_blocksize_bits);
			else {
				memmove(&laarr[c + 2], &laarr[c + 1],
					sizeof(struct long_ad) * (*endnum - (c + 1)));
				(*endnum)++;
				laarr[c + 1].extLocation.logicalBlockNum = next;
				laarr[c + 1].extLocation.partitionReferenceNum =
					laarr[c].extLocation.
							partitionReferenceNum;
				laarr[c + 1].extLength =
					EXT_NOT_RECORDED_ALLOCATED |
					(numalloc <<
					 inode->i_sb->s_blocksize_bits);
				start = c + 1;
			}

			for (i = start + 1; numalloc && i < *endnum; i++) {
				int elen = ((laarr[i].extLength &
						UDF_EXTENT_LENGTH_MASK) +
					    inode->i_sb->s_blocksize - 1) >>
					    inode->i_sb->s_blocksize_bits;

				if (elen > numalloc) {
					laarr[i].extLength -=
						(numalloc <<
						 inode->i_sb->s_blocksize_bits);
					numalloc = 0;
				} else {
					numalloc -= elen;
					if (*endnum > (i + 1))
						memmove(&laarr[i],
							&laarr[i + 1],
							sizeof(struct long_ad) *
							(*endnum - (i + 1)));
					i--;
					(*endnum)--;
				}
			}
			UDF_I(inode)->i_lenExtents +=
				numalloc << inode->i_sb->s_blocksize_bits;
		}
	}
}