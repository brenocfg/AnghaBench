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
struct swap_info_struct {int flags; int /*<<< orphan*/  list; scalar_t__ pages; } ;

/* Variables and functions */
 int SWP_VALID ; 
 int SWP_WRITEOK ; 
 int /*<<< orphan*/  add_to_avail_list (struct swap_info_struct*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_add (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_swap_pages ; 
 int /*<<< orphan*/  plist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_active_head ; 
 int /*<<< orphan*/  swap_lock ; 
 int /*<<< orphan*/  total_swap_pages ; 

__attribute__((used)) static void _enable_swap_info(struct swap_info_struct *p)
{
	p->flags |= SWP_WRITEOK | SWP_VALID;
	atomic_long_add(p->pages, &nr_swap_pages);
	total_swap_pages += p->pages;

	assert_spin_locked(&swap_lock);
	/*
	 * both lists are plists, and thus priority ordered.
	 * swap_active_head needs to be priority ordered for swapoff(),
	 * which on removal of any swap_info_struct with an auto-assigned
	 * (i.e. negative) priority increments the auto-assigned priority
	 * of any lower-priority swap_info_structs.
	 * swap_avail_head needs to be priority ordered for get_swap_page(),
	 * which allocates swap pages from the highest available priority
	 * swap_info_struct.
	 */
	plist_add(&p->list, &swap_active_head);
	add_to_avail_list(p);
}