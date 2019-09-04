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
struct pcifront_device {TYPE_1__* xdev; } ;
typedef  int /*<<< orphan*/  str ;
struct TYPE_4__ {int /*<<< orphan*/  otherend; int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int EEXIST ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  XenbusStateConnected ; 
 scalar_t__ XenbusStateInitialised ; 
 int pcifront_connect_and_init_dma (struct pcifront_device*) ; 
 int pcifront_scan_root (struct pcifront_device*,unsigned int,unsigned int) ; 
 int snprintf (char*,int,char*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xenbus_dev_error (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (TYPE_1__*,int,char*,...) ; 
 scalar_t__ xenbus_read_driver_state (int /*<<< orphan*/ ) ; 
 int xenbus_scanf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,...) ; 
 int xenbus_switch_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcifront_try_connect(struct pcifront_device *pdev)
{
	int err = -EFAULT;
	int i, num_roots, len;
	char str[64];
	unsigned int domain, bus;


	/* Only connect once */
	if (xenbus_read_driver_state(pdev->xdev->nodename) !=
	    XenbusStateInitialised)
		goto out;

	err = pcifront_connect_and_init_dma(pdev);
	if (err && err != -EEXIST) {
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error setting up PCI Frontend");
		goto out;
	}

	err = xenbus_scanf(XBT_NIL, pdev->xdev->otherend,
			   "root_num", "%d", &num_roots);
	if (err == -ENOENT) {
		xenbus_dev_error(pdev->xdev, err,
				 "No PCI Roots found, trying 0000:00");
		err = pcifront_scan_root(pdev, 0, 0);
		if (err) {
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error scanning PCI root 0000:00");
			goto out;
		}
		num_roots = 0;
	} else if (err != 1) {
		if (err == 0)
			err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error reading number of PCI roots");
		goto out;
	}

	for (i = 0; i < num_roots; i++) {
		len = snprintf(str, sizeof(str), "root-%d", i);
		if (unlikely(len >= (sizeof(str) - 1))) {
			err = -ENOMEM;
			goto out;
		}

		err = xenbus_scanf(XBT_NIL, pdev->xdev->otherend, str,
				   "%x:%x", &domain, &bus);
		if (err != 2) {
			if (err >= 0)
				err = -EINVAL;
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error reading PCI root %d", i);
			goto out;
		}

		err = pcifront_scan_root(pdev, domain, bus);
		if (err) {
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error scanning PCI root %04x:%02x",
					 domain, bus);
			goto out;
		}
	}

	err = xenbus_switch_state(pdev->xdev, XenbusStateConnected);

out:
	return err;
}