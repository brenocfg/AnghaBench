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
struct switchdev_trans_item {int /*<<< orphan*/  data; int /*<<< orphan*/  (* destructor ) (int /*<<< orphan*/ ) ;} ;
struct switchdev_trans {int dummy; } ;

/* Variables and functions */
 struct switchdev_trans_item* __switchdev_trans_item_dequeue (struct switchdev_trans*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void switchdev_trans_items_destroy(struct switchdev_trans *trans)
{
	struct switchdev_trans_item *tritem;

	while ((tritem = __switchdev_trans_item_dequeue(trans)))
		tritem->destructor(tritem->data);
}