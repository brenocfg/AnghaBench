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
struct switchdev_trans_item {void* data; } ;
struct switchdev_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct switchdev_trans_item* __switchdev_trans_item_dequeue (struct switchdev_trans*) ; 

void *switchdev_trans_item_dequeue(struct switchdev_trans *trans)
{
	struct switchdev_trans_item *tritem;

	tritem = __switchdev_trans_item_dequeue(trans);
	BUG_ON(!tritem);
	return tritem->data;
}