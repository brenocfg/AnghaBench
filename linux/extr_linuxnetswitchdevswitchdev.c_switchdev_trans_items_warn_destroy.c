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
struct switchdev_trans {int /*<<< orphan*/  item_list; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switchdev_trans_items_destroy (struct switchdev_trans*) ; 

__attribute__((used)) static void switchdev_trans_items_warn_destroy(struct net_device *dev,
					       struct switchdev_trans *trans)
{
	WARN(!list_empty(&trans->item_list), "%s: transaction item queue is not empty.\n",
	     dev->name);
	switchdev_trans_items_destroy(trans);
}