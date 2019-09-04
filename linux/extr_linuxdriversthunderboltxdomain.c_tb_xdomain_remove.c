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
struct tb_xdomain {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child_reverse (int /*<<< orphan*/ *,struct tb_xdomain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_handshake (struct tb_xdomain*) ; 
 int /*<<< orphan*/  unregister_service ; 

void tb_xdomain_remove(struct tb_xdomain *xd)
{
	stop_handshake(xd);

	device_for_each_child_reverse(&xd->dev, xd, unregister_service);

	/*
	 * Undo runtime PM here explicitly because it is possible that
	 * the XDomain was never added to the bus and thus device_del()
	 * is not called for it (device_del() would handle this otherwise).
	 */
	pm_runtime_disable(&xd->dev);
	pm_runtime_put_noidle(&xd->dev);
	pm_runtime_set_suspended(&xd->dev);

	if (!device_is_registered(&xd->dev))
		put_device(&xd->dev);
	else
		device_unregister(&xd->dev);
}