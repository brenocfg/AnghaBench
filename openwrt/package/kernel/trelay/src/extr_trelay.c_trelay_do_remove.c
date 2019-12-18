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
struct trelay {int /*<<< orphan*/  dev2; int /*<<< orphan*/  dev1; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct trelay*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trelay_log (int /*<<< orphan*/ ,struct trelay*,char*) ; 

__attribute__((used)) static int trelay_do_remove(struct trelay *tr)
{
	list_del(&tr->list);

	/* First and before all, ensure that the debugfs file is removed
	 * to prevent dangling pointer in file->private_data */
	debugfs_remove_recursive(tr->debugfs);

	dev_put(tr->dev1);
	dev_put(tr->dev2);

	netdev_rx_handler_unregister(tr->dev1);
	netdev_rx_handler_unregister(tr->dev2);

	trelay_log(KERN_INFO, tr, "stopped");

	kfree(tr);

	return 0;
}