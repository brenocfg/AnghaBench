#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int s_blocksize_bits; int s_blocksize; } ;
typedef  int b_blocknr_t ;

/* Variables and functions */

__attribute__((used)) static inline void get_bit_address(struct super_block *s,
				   b_blocknr_t block,
				   unsigned int *bmap_nr,
				   unsigned int *offset)
{
	/*
	 * It is in the bitmap block number equal to the block
	 * number divided by the number of bits in a block.
	 */
	*bmap_nr = block >> (s->s_blocksize_bits + 3);
	/* Within that bitmap block it is located at bit offset *offset. */
	*offset = block & ((s->s_blocksize << 3) - 1);
}