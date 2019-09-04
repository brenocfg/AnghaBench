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
 int /*<<< orphan*/  fe_watch ; 
 int /*<<< orphan*/  register_xenbus_watch (int /*<<< orphan*/ *) ; 
 scalar_t__ xen_hvm_domain () ; 
 int /*<<< orphan*/  xenbus_frontend ; 
 int /*<<< orphan*/  xenbus_probe_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_reset_state () ; 

__attribute__((used)) static int frontend_probe_and_watch(struct notifier_block *notifier,
				   unsigned long event,
				   void *data)
{
	/* reset devices in Connected or Closed state */
	if (xen_hvm_domain())
		xenbus_reset_state();
	/* Enumerate devices in xenstore and watch for changes. */
	xenbus_probe_devices(&xenbus_frontend);
	register_xenbus_watch(&fe_watch);

	return NOTIFY_DONE;
}