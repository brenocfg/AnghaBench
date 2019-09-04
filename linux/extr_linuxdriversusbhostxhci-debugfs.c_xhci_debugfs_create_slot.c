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
struct xhci_virt_device {TYPE_1__* eps; struct xhci_slot_priv* debugfs_private; } ;
struct xhci_slot_priv {int /*<<< orphan*/  root; struct xhci_virt_device* dev; int /*<<< orphan*/  name; } ;
struct xhci_hcd {int /*<<< orphan*/  debugfs_slots; struct xhci_virt_device** devs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xhci_slot_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  xhci_debugfs_create_context_files (struct xhci_hcd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xhci_debugfs_create_ring_dir (struct xhci_hcd*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void xhci_debugfs_create_slot(struct xhci_hcd *xhci, int slot_id)
{
	struct xhci_slot_priv	*priv;
	struct xhci_virt_device	*dev = xhci->devs[slot_id];

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return;

	snprintf(priv->name, sizeof(priv->name), "%02d", slot_id);
	priv->root = debugfs_create_dir(priv->name, xhci->debugfs_slots);
	priv->dev = dev;
	dev->debugfs_private = priv;

	xhci_debugfs_create_ring_dir(xhci, &dev->eps[0].ring,
				     "ep00", priv->root);

	xhci_debugfs_create_context_files(xhci, priv->root, slot_id);
}