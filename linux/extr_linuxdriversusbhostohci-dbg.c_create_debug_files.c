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
struct usb_bus {int /*<<< orphan*/  bus_name; } ;
struct ohci_hcd {struct dentry* debug_dir; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct usb_bus self; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debug_async_fops ; 
 int /*<<< orphan*/  debug_periodic_fops ; 
 int /*<<< orphan*/  debug_registers_fops ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct ohci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_dbg (struct ohci_hcd*,char*) ; 
 int /*<<< orphan*/  ohci_debug_root ; 
 TYPE_1__* ohci_to_hcd (struct ohci_hcd*) ; 

__attribute__((used)) static inline void create_debug_files (struct ohci_hcd *ohci)
{
	struct usb_bus *bus = &ohci_to_hcd(ohci)->self;
	struct dentry *root;

	root = debugfs_create_dir(bus->bus_name, ohci_debug_root);
	ohci->debug_dir = root;

	debugfs_create_file("async", S_IRUGO, root, ohci, &debug_async_fops);
	debugfs_create_file("periodic", S_IRUGO, root, ohci,
			    &debug_periodic_fops);
	debugfs_create_file("registers", S_IRUGO, root, ohci,
			    &debug_registers_fops);

	ohci_dbg (ohci, "created debug files\n");
}