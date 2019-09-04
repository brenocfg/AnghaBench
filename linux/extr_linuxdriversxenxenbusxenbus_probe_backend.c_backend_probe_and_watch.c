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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  be_watch ; 
 int /*<<< orphan*/  register_xenbus_watch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_backend ; 
 int /*<<< orphan*/  xenbus_probe_devices (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int backend_probe_and_watch(struct notifier_block *notifier,
				   unsigned long event,
				   void *data)
{
	/* Enumerate devices in xenstore and watch for changes. */
	xenbus_probe_devices(&xenbus_backend);
	register_xenbus_watch(&be_watch);

	return NOTIFY_DONE;
}