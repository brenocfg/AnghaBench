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
struct ext4_buddy {int bd_blkbits; void* bd_buddy; void* bd_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mb_test_bit (int,void*) ; 

__attribute__((used)) static int mb_find_order_for_block(struct ext4_buddy *e4b, int block)
{
	int order = 1;
	int bb_incr = 1 << (e4b->bd_blkbits - 1);
	void *bb;

	BUG_ON(e4b->bd_bitmap == e4b->bd_buddy);
	BUG_ON(block >= (1 << (e4b->bd_blkbits + 3)));

	bb = e4b->bd_buddy;
	while (order <= e4b->bd_blkbits + 1) {
		block = block >> 1;
		if (!mb_test_bit(block, bb)) {
			/* this block is part of buddy of order 'order' */
			return order;
		}
		bb += bb_incr;
		bb_incr >>= 1;
		order++;
	}
	return 0;
}