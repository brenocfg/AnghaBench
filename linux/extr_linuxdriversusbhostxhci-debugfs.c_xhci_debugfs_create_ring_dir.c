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
struct xhci_ring {int dummy; } ;
struct xhci_hcd {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_dir (char const*,struct dentry*) ; 
 int /*<<< orphan*/  ring_files ; 
 int /*<<< orphan*/  xhci_debugfs_create_files (struct xhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xhci_ring**,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_ring_fops ; 

__attribute__((used)) static struct dentry *xhci_debugfs_create_ring_dir(struct xhci_hcd *xhci,
						   struct xhci_ring **ring,
						   const char *name,
						   struct dentry *parent)
{
	struct dentry		*dir;

	dir = debugfs_create_dir(name, parent);
	xhci_debugfs_create_files(xhci, ring_files, ARRAY_SIZE(ring_files),
				  ring, dir, &xhci_ring_fops);

	return dir;
}