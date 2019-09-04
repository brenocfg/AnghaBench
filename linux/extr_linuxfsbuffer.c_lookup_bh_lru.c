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
struct buffer_head {scalar_t__ b_blocknr; unsigned int b_size; struct block_device* b_bdev; } ;
struct block_device {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {int /*<<< orphan*/ * bhs; } ;

/* Variables and functions */
 unsigned int BH_LRU_SIZE ; 
 struct buffer_head* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  bh_lru_lock () ; 
 int /*<<< orphan*/  bh_lru_unlock () ; 
 TYPE_1__ bh_lrus ; 
 int /*<<< orphan*/  check_irqs_on () ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 

__attribute__((used)) static struct buffer_head *
lookup_bh_lru(struct block_device *bdev, sector_t block, unsigned size)
{
	struct buffer_head *ret = NULL;
	unsigned int i;

	check_irqs_on();
	bh_lru_lock();
	for (i = 0; i < BH_LRU_SIZE; i++) {
		struct buffer_head *bh = __this_cpu_read(bh_lrus.bhs[i]);

		if (bh && bh->b_blocknr == block && bh->b_bdev == bdev &&
		    bh->b_size == size) {
			if (i) {
				while (i) {
					__this_cpu_write(bh_lrus.bhs[i],
						__this_cpu_read(bh_lrus.bhs[i - 1]));
					i--;
				}
				__this_cpu_write(bh_lrus.bhs[0], bh);
			}
			get_bh(bh);
			ret = bh;
			break;
		}
	}
	bh_lru_unlock();
	return ret;
}