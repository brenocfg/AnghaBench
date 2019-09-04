#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xen_pcibk_device {int /*<<< orphan*/  dev_lock; TYPE_1__* xdev; } ;
typedef  int /*<<< orphan*/  state_str ;
typedef  int /*<<< orphan*/  dev_str ;
struct TYPE_3__ {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  XBT_NIL ; 
 scalar_t__ XenbusStateInitWait ; 
 int /*<<< orphan*/  XenbusStateInitialised ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xen_pcibk_attach (struct xen_pcibk_device*) ; 
 int xen_pcibk_export_device (struct xen_pcibk_device*,int,int,int,int,int) ; 
 int /*<<< orphan*/  xen_pcibk_publish_pci_root ; 
 int xen_pcibk_publish_pci_roots (struct xen_pcibk_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (TYPE_1__*,int,char*,...) ; 
 int xenbus_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ xenbus_read_driver_state (int /*<<< orphan*/ ) ; 
 int xenbus_scanf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int*,...) ; 
 int xenbus_switch_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xen_pcibk_setup_backend(struct xen_pcibk_device *pdev)
{
	/* Get configuration from xend (if available now) */
	int domain, bus, slot, func;
	int err = 0;
	int i, num_devs;
	char dev_str[64];
	char state_str[64];

	mutex_lock(&pdev->dev_lock);
	/* It's possible we could get the call to setup twice, so make sure
	 * we're not already connected.
	 */
	if (xenbus_read_driver_state(pdev->xdev->nodename) !=
	    XenbusStateInitWait)
		goto out;

	dev_dbg(&pdev->xdev->dev, "getting be setup\n");

	err = xenbus_scanf(XBT_NIL, pdev->xdev->nodename, "num_devs", "%d",
			   &num_devs);
	if (err != 1) {
		if (err >= 0)
			err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error reading number of devices");
		goto out;
	}

	for (i = 0; i < num_devs; i++) {
		int l = snprintf(dev_str, sizeof(dev_str), "dev-%d", i);
		if (unlikely(l >= (sizeof(dev_str) - 1))) {
			err = -ENOMEM;
			xenbus_dev_fatal(pdev->xdev, err,
					 "String overflow while reading "
					 "configuration");
			goto out;
		}

		err = xenbus_scanf(XBT_NIL, pdev->xdev->nodename, dev_str,
				   "%x:%x:%x.%x", &domain, &bus, &slot, &func);
		if (err < 0) {
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error reading device configuration");
			goto out;
		}
		if (err != 4) {
			err = -EINVAL;
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error parsing pci device "
					 "configuration");
			goto out;
		}

		err = xen_pcibk_export_device(pdev, domain, bus, slot, func, i);
		if (err)
			goto out;

		/* Switch substate of this device. */
		l = snprintf(state_str, sizeof(state_str), "state-%d", i);
		if (unlikely(l >= (sizeof(state_str) - 1))) {
			err = -ENOMEM;
			xenbus_dev_fatal(pdev->xdev, err,
					 "String overflow while reading "
					 "configuration");
			goto out;
		}
		err = xenbus_printf(XBT_NIL, pdev->xdev->nodename, state_str,
				    "%d", XenbusStateInitialised);
		if (err) {
			xenbus_dev_fatal(pdev->xdev, err, "Error switching "
					 "substate of dev-%d\n", i);
			goto out;
		}
	}

	err = xen_pcibk_publish_pci_roots(pdev, xen_pcibk_publish_pci_root);
	if (err) {
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error while publish PCI root buses "
				 "for frontend");
		goto out;
	}

	err = xenbus_switch_state(pdev->xdev, XenbusStateInitialised);
	if (err)
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error switching to initialised state!");

out:
	mutex_unlock(&pdev->dev_lock);
	if (!err)
		/* see if pcifront is already configured (if not, we'll wait) */
		xen_pcibk_attach(pdev);
	return err;
}