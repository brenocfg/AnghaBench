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
struct TYPE_2__ {int /*<<< orphan*/ * bitmap; } ;
union afs_xdr_dir_block {TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static void afs_clear_contig_bits(union afs_xdr_dir_block *block,
				  int bit, unsigned int nr_slots)
{
	u64 mask, before, after;

	mask = (1 << nr_slots) - 1;
	mask <<= bit;

	before = *(u64 *)block->hdr.bitmap;

	block->hdr.bitmap[0] &= ~(u8)(mask >> 0 * 8);
	block->hdr.bitmap[1] &= ~(u8)(mask >> 1 * 8);
	block->hdr.bitmap[2] &= ~(u8)(mask >> 2 * 8);
	block->hdr.bitmap[3] &= ~(u8)(mask >> 3 * 8);
	block->hdr.bitmap[4] &= ~(u8)(mask >> 4 * 8);
	block->hdr.bitmap[5] &= ~(u8)(mask >> 5 * 8);
	block->hdr.bitmap[6] &= ~(u8)(mask >> 6 * 8);
	block->hdr.bitmap[7] &= ~(u8)(mask >> 7 * 8);

	after = *(u64 *)block->hdr.bitmap;
}