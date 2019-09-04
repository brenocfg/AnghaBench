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
struct xhci_virt_device {int /*<<< orphan*/  debugfs_private; } ;
struct xhci_hcd {struct xhci_virt_device** devs; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_files ; 
 int /*<<< orphan*/  xhci_context_fops ; 
 int /*<<< orphan*/  xhci_debugfs_create_files (struct xhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xhci_debugfs_create_context_files(struct xhci_hcd *xhci,
					      struct dentry *parent,
					      int slot_id)
{
	struct xhci_virt_device	*dev = xhci->devs[slot_id];

	xhci_debugfs_create_files(xhci, context_files,
				  ARRAY_SIZE(context_files),
				  dev->debugfs_private,
				  parent, &xhci_context_fops);
}