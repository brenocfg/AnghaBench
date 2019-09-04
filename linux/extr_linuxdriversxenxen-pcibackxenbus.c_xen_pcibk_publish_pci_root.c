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
struct xen_pcibk_device {TYPE_1__* xdev; } ;
typedef  int /*<<< orphan*/  str ;
struct TYPE_2__ {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int snprintf (char*,int,char*,int) ; 
 scalar_t__ unlikely (int) ; 
 int xenbus_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int,...) ; 
 int xenbus_scanf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static int xen_pcibk_publish_pci_root(struct xen_pcibk_device *pdev,
				    unsigned int domain, unsigned int bus)
{
	unsigned int d, b;
	int i, root_num, len, err;
	char str[64];

	dev_dbg(&pdev->xdev->dev, "Publishing pci roots\n");

	err = xenbus_scanf(XBT_NIL, pdev->xdev->nodename,
			   "root_num", "%d", &root_num);
	if (err == 0 || err == -ENOENT)
		root_num = 0;
	else if (err < 0)
		goto out;

	/* Verify that we haven't already published this pci root */
	for (i = 0; i < root_num; i++) {
		len = snprintf(str, sizeof(str), "root-%d", i);
		if (unlikely(len >= (sizeof(str) - 1))) {
			err = -ENOMEM;
			goto out;
		}

		err = xenbus_scanf(XBT_NIL, pdev->xdev->nodename,
				   str, "%x:%x", &d, &b);
		if (err < 0)
			goto out;
		if (err != 2) {
			err = -EINVAL;
			goto out;
		}

		if (d == domain && b == bus) {
			err = 0;
			goto out;
		}
	}

	len = snprintf(str, sizeof(str), "root-%d", root_num);
	if (unlikely(len >= (sizeof(str) - 1))) {
		err = -ENOMEM;
		goto out;
	}

	dev_dbg(&pdev->xdev->dev, "writing root %d at %04x:%02x\n",
		root_num, domain, bus);

	err = xenbus_printf(XBT_NIL, pdev->xdev->nodename, str,
			    "%04x:%02x", domain, bus);
	if (err)
		goto out;

	err = xenbus_printf(XBT_NIL, pdev->xdev->nodename,
			    "root_num", "%d", (root_num + 1));

out:
	return err;
}