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
struct address_space {scalar_t__ nrpages; } ;

/* Variables and functions */
 unsigned int MAX_SWAPFILES ; 
 unsigned int* nr_swapper_spaces ; 
 struct address_space* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/ * swapper_spaces ; 

unsigned long total_swapcache_pages(void)
{
	unsigned int i, j, nr;
	unsigned long ret = 0;
	struct address_space *spaces;

	rcu_read_lock();
	for (i = 0; i < MAX_SWAPFILES; i++) {
		/*
		 * The corresponding entries in nr_swapper_spaces and
		 * swapper_spaces will be reused only after at least
		 * one grace period.  So it is impossible for them
		 * belongs to different usage.
		 */
		nr = nr_swapper_spaces[i];
		spaces = rcu_dereference(swapper_spaces[i]);
		if (!nr || !spaces)
			continue;
		for (j = 0; j < nr; j++)
			ret += spaces[j].nrpages;
	}
	rcu_read_unlock();
	return ret;
}