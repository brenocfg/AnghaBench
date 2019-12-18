#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* bitmap; } ;
union afs_xdr_dir_block {TYPE_1__ hdr; } ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int __ffs (int) ; 
 int ffz (scalar_t__) ; 

__attribute__((used)) static int afs_find_contig_bits(union afs_xdr_dir_block *block, unsigned int nr_slots)
{
	u64 bitmap;
	u32 mask;
	int bit, n;

	bitmap  = (u64)block->hdr.bitmap[0] << 0 * 8;
	bitmap |= (u64)block->hdr.bitmap[1] << 1 * 8;
	bitmap |= (u64)block->hdr.bitmap[2] << 2 * 8;
	bitmap |= (u64)block->hdr.bitmap[3] << 3 * 8;
	bitmap |= (u64)block->hdr.bitmap[4] << 4 * 8;
	bitmap |= (u64)block->hdr.bitmap[5] << 5 * 8;
	bitmap |= (u64)block->hdr.bitmap[6] << 6 * 8;
	bitmap |= (u64)block->hdr.bitmap[7] << 7 * 8;
	bitmap >>= 1; /* The first entry is metadata */
	bit = 1;
	mask = (1 << nr_slots) - 1;

	do {
		if (sizeof(unsigned long) == 8)
			n = ffz(bitmap);
		else
			n = ((u32)bitmap) != 0 ?
				ffz((u32)bitmap) :
				ffz((u32)(bitmap >> 32)) + 32;
		bitmap >>= n;
		bit += n;

		if ((bitmap & mask) == 0) {
			if (bit > 64 - nr_slots)
				return -1;
			return bit;
		}

		n = __ffs(bitmap);
		bitmap >>= n;
		bit += n;
	} while (bitmap);

	return -1;
}