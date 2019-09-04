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
struct xen_pcibk_device {int dummy; } ;
typedef  int (* publish_pci_root_cb ) (struct xen_pcibk_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */

__attribute__((used)) static int __xen_pcibk_publish_pci_roots(struct xen_pcibk_device *pdev,
					 publish_pci_root_cb publish_cb)
{
	/* The Virtual PCI bus has only one root */
	return publish_cb(pdev, 0, 0);
}