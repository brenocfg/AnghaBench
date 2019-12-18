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
struct bh_lru {int /*<<< orphan*/ * bhs; } ;

/* Variables and functions */
 int BH_LRU_SIZE ; 
 int /*<<< orphan*/  bh_lru_lock () ; 
 int /*<<< orphan*/  bh_lru_unlock () ; 
 int /*<<< orphan*/  bh_lrus ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  check_irqs_on () ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  swap (struct buffer_head*,int /*<<< orphan*/ ) ; 
 struct bh_lru* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bh_lru_install(struct buffer_head *bh)
{
	struct buffer_head *evictee = bh;
	struct bh_lru *b;
	int i;

	check_irqs_on();
	bh_lru_lock();

	b = this_cpu_ptr(&bh_lrus);
	for (i = 0; i < BH_LRU_SIZE; i++) {
		swap(evictee, b->bhs[i]);
		if (evictee == bh) {
			bh_lru_unlock();
			return;
		}
	}

	get_bh(bh);
	bh_lru_unlock();
	brelse(evictee);
}