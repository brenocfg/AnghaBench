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
struct parman_prio {int /*<<< orphan*/  item_list; } ;
struct parman_item {unsigned long index; int /*<<< orphan*/  list; } ;
struct parman {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __parman_prio_move (struct parman*,struct parman_prio*,struct parman_item*,unsigned long,int) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct parman_item* parman_prio_first_item (struct parman_prio*) ; 
 int parman_prio_last_index (struct parman_prio*) ; 
 int /*<<< orphan*/  parman_prio_used (struct parman_prio*) ; 

__attribute__((used)) static void parman_prio_shift_down(struct parman *parman,
				   struct parman_prio *prio)
{
	struct parman_item *item;
	unsigned long to_index;

	if (!parman_prio_used(prio))
		return;
	item = parman_prio_first_item(prio);
	to_index = parman_prio_last_index(prio) + 1;
	__parman_prio_move(parman, prio, item, to_index, 1);
	list_move_tail(&item->list, &prio->item_list);
	item->index = to_index;
}