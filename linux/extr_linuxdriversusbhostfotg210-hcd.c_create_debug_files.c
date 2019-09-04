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
struct fotg210_hcd {struct dentry* debug_dir; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct usb_bus self; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debug_async_fops ; 
 int /*<<< orphan*/  debug_periodic_fops ; 
 int /*<<< orphan*/  debug_registers_fops ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct usb_bus*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fotg210_debug_root ; 
 TYPE_1__* fotg210_to_hcd (struct fotg210_hcd*) ; 

__attribute__((used)) static inline void create_debug_files(struct fotg210_hcd *fotg210)
{
	struct usb_bus *bus = &fotg210_to_hcd(fotg210)->self;
	struct dentry *root;

	root = debugfs_create_dir(bus->bus_name, fotg210_debug_root);
	fotg210->debug_dir = root;

	debugfs_create_file("async", S_IRUGO, root, bus, &debug_async_fops);
	debugfs_create_file("periodic", S_IRUGO, root, bus,
			    &debug_periodic_fops);
	debugfs_create_file("registers", S_IRUGO, root, bus,
			    &debug_registers_fops);
}