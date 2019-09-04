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
struct gb_svc {int /*<<< orphan*/  connection; int /*<<< orphan*/  wq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_disable_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_svc_debugfs_exit (struct gb_svc*) ; 
 int /*<<< orphan*/  gb_svc_remove_modules (struct gb_svc*) ; 
 int /*<<< orphan*/  gb_svc_watchdog_destroy (struct gb_svc*) ; 

void gb_svc_del(struct gb_svc *svc)
{
	gb_connection_disable_rx(svc->connection);

	/*
	 * The SVC device may have been registered from the request handler.
	 */
	if (device_is_registered(&svc->dev)) {
		gb_svc_debugfs_exit(svc);
		gb_svc_watchdog_destroy(svc);
		device_del(&svc->dev);
	}

	flush_workqueue(svc->wq);

	gb_svc_remove_modules(svc);

	gb_connection_disable(svc->connection);
}