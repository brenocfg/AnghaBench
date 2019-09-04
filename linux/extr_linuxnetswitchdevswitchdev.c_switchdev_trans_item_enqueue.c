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
struct switchdev_trans_item {void (* destructor ) (void const*) ;int /*<<< orphan*/  list; void* data; } ;
struct switchdev_trans {int /*<<< orphan*/  item_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void switchdev_trans_item_enqueue(struct switchdev_trans *trans,
				  void *data, void (*destructor)(void const *),
				  struct switchdev_trans_item *tritem)
{
	tritem->data = data;
	tritem->destructor = destructor;
	list_add_tail(&tritem->list, &trans->item_list);
}