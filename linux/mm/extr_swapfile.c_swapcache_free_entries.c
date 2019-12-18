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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  entries ;

/* Variables and functions */
 int nr_swapfiles ; 
 int /*<<< orphan*/  sort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_entry_free (struct swap_info_struct*,int /*<<< orphan*/ ) ; 
 struct swap_info_struct* swap_info_get_cont (int /*<<< orphan*/ ,struct swap_info_struct*) ; 
 int /*<<< orphan*/  swp_entry_cmp ; 

void swapcache_free_entries(swp_entry_t *entries, int n)
{
	struct swap_info_struct *p, *prev;
	int i;

	if (n <= 0)
		return;

	prev = NULL;
	p = NULL;

	/*
	 * Sort swap entries by swap device, so each lock is only taken once.
	 * nr_swapfiles isn't absolutely correct, but the overhead of sort() is
	 * so low that it isn't necessary to optimize further.
	 */
	if (nr_swapfiles > 1)
		sort(entries, n, sizeof(entries[0]), swp_entry_cmp, NULL);
	for (i = 0; i < n; ++i) {
		p = swap_info_get_cont(entries[i], prev);
		if (p)
			swap_entry_free(p, entries[i]);
		prev = p;
	}
	if (p)
		spin_unlock(&p->lock);
}