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
struct xhci_port {int dummy; } ;
struct xhci_hcd {struct xhci_port* hw_ports; int /*<<< orphan*/  hcs_params1; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  port_name ;

/* Variables and functions */
 unsigned int HCS_MAX_PORTS (int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct xhci_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_fops ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static void xhci_debugfs_create_ports(struct xhci_hcd *xhci,
				      struct dentry *parent)
{
	unsigned int		num_ports;
	char			port_name[8];
	struct xhci_port	*port;
	struct dentry		*dir;

	num_ports = HCS_MAX_PORTS(xhci->hcs_params1);

	parent = debugfs_create_dir("ports", parent);

	while (num_ports--) {
		scnprintf(port_name, sizeof(port_name), "port%02d",
			  num_ports + 1);
		dir = debugfs_create_dir(port_name, parent);
		port = &xhci->hw_ports[num_ports];
		debugfs_create_file("portsc", 0644, dir, port, &port_fops);
	}
}