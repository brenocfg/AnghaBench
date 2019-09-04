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
struct list_head {struct list_head* next; struct list_head* prev; } ;

/* Variables and functions */
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_splice_init_rcu (struct list_head*,struct list_head*,int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void smk_list_swap_rcu(struct list_head *public,
			      struct list_head *private)
{
	struct list_head *first, *last;

	if (list_empty(public)) {
		list_splice_init_rcu(private, public, synchronize_rcu);
	} else {
		/* Remember public list before replacing it */
		first = public->next;
		last = public->prev;

		/* Publish private list in place of public in RCU-safe way */
		private->prev->next = public;
		private->next->prev = public;
		rcu_assign_pointer(public->next, private->next);
		public->prev = private->prev;

		synchronize_rcu();

		/* When all readers are done with the old public list,
		 * attach it in place of private */
		private->next = first;
		private->prev = last;
		first->prev = private;
		last->next = private;
	}
}