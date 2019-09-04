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
struct parman_prio {int dummy; } ;
struct parman_item {unsigned long index; int /*<<< orphan*/  list; } ;
struct parman {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __parman_prio_move (struct parman*,struct parman_prio*,struct parman_item*,unsigned long,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct parman_item* parman_prio_last_item (struct parman_prio*) ; 

__attribute__((used)) static void parman_prio_item_remove(struct parman *parman,
				    struct parman_prio *prio,
				    struct parman_item *item)
{
	struct parman_item *last_item;
	unsigned long to_index;

	last_item = parman_prio_last_item(prio);
	if (last_item == item) {
		list_del(&item->list);
		return;
	}
	to_index = item->index;
	__parman_prio_move(parman, prio, last_item, to_index, 1);
	list_del(&last_item->list);
	list_replace(&item->list, &last_item->list);
	last_item->index = to_index;
}