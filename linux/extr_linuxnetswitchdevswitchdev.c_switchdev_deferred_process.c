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
struct switchdev_deferred_item {int /*<<< orphan*/  dev; int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct switchdev_deferred_item*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct switchdev_deferred_item* switchdev_deferred_dequeue () ; 

void switchdev_deferred_process(void)
{
	struct switchdev_deferred_item *dfitem;

	ASSERT_RTNL();

	while ((dfitem = switchdev_deferred_dequeue())) {
		dfitem->func(dfitem->dev, dfitem->data);
		dev_put(dfitem->dev);
		kfree(dfitem);
	}
}