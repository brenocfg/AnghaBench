#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcifront_device {TYPE_1__* xdev; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;
struct TYPE_2__ {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int /*<<< orphan*/  XenbusStateClosed ; 
 int XenbusStateClosing ; 
 int XenbusStateConnected ; 
 int /*<<< orphan*/  pcifront_disconnect (struct pcifront_device*) ; 
 int /*<<< orphan*/  pcifront_free_roots (struct pcifront_device*) ; 
 int xenbus_read_driver_state (int /*<<< orphan*/ ) ; 
 int xenbus_switch_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcifront_try_disconnect(struct pcifront_device *pdev)
{
	int err = 0;
	enum xenbus_state prev_state;


	prev_state = xenbus_read_driver_state(pdev->xdev->nodename);

	if (prev_state >= XenbusStateClosing)
		goto out;

	if (prev_state == XenbusStateConnected) {
		pcifront_free_roots(pdev);
		pcifront_disconnect(pdev);
	}

	err = xenbus_switch_state(pdev->xdev, XenbusStateClosed);

out:

	return err;
}