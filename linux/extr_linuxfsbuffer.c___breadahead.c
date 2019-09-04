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
struct buffer_head {int dummy; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  REQ_RAHEAD ; 
 struct buffer_head* __getblk (struct block_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ likely (struct buffer_head*) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct buffer_head**) ; 

void __breadahead(struct block_device *bdev, sector_t block, unsigned size)
{
	struct buffer_head *bh = __getblk(bdev, block, size);
	if (likely(bh)) {
		ll_rw_block(REQ_OP_READ, REQ_RAHEAD, 1, &bh);
		brelse(bh);
	}
}