#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct usb_port {scalar_t__ location; int is_superspeed; TYPE_1__ dev; struct usb_port* peer; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 char* dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int link_peers(struct usb_port *left, struct usb_port *right)
{
	struct usb_port *ss_port, *hs_port;
	int rc;

	if (left->peer == right && right->peer == left)
		return 0;

	if (left->peer || right->peer) {
		struct usb_port *lpeer = left->peer;
		struct usb_port *rpeer = right->peer;
		char *method;

		if (left->location && left->location == right->location)
			method = "location";
		else
			method = "default";

		pr_debug("usb: failed to peer %s and %s by %s (%s:%s) (%s:%s)\n",
			dev_name(&left->dev), dev_name(&right->dev), method,
			dev_name(&left->dev),
			lpeer ? dev_name(&lpeer->dev) : "none",
			dev_name(&right->dev),
			rpeer ? dev_name(&rpeer->dev) : "none");
		return -EBUSY;
	}

	rc = sysfs_create_link(&left->dev.kobj, &right->dev.kobj, "peer");
	if (rc)
		return rc;
	rc = sysfs_create_link(&right->dev.kobj, &left->dev.kobj, "peer");
	if (rc) {
		sysfs_remove_link(&left->dev.kobj, "peer");
		return rc;
	}

	/*
	 * We need to wake the HiSpeed port to make sure we don't race
	 * setting ->peer with usb_port_runtime_suspend().  Otherwise we
	 * may miss a suspend event for the SuperSpeed port.
	 */
	if (left->is_superspeed) {
		ss_port = left;
		WARN_ON(right->is_superspeed);
		hs_port = right;
	} else {
		ss_port = right;
		WARN_ON(!right->is_superspeed);
		hs_port = left;
	}
	pm_runtime_get_sync(&hs_port->dev);

	left->peer = right;
	right->peer = left;

	/*
	 * The SuperSpeed reference is dropped when the HiSpeed port in
	 * this relationship suspends, i.e. when it is safe to allow a
	 * SuperSpeed connection to drop since there is no risk of a
	 * device degrading to its powered-off HiSpeed connection.
	 *
	 * Also, drop the HiSpeed ref taken above.
	 */
	pm_runtime_get_sync(&ss_port->dev);
	pm_runtime_put(&hs_port->dev);

	return 0;
}