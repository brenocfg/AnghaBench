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
struct xen_bus_type {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int xenbus_probe_node (struct xen_bus_type*,char const*,char*) ; 

__attribute__((used)) static int xenbus_probe_frontend(struct xen_bus_type *bus, const char *type,
				 const char *name)
{
	char *nodename;
	int err;

	/* ignore console/0 */
	if (!strncmp(type, "console", 7) && !strncmp(name, "0", 1)) {
		DPRINTK("Ignoring buggy device entry console/0");
		return 0;
	}

	nodename = kasprintf(GFP_KERNEL, "%s/%s/%s", bus->root, type, name);
	if (!nodename)
		return -ENOMEM;

	DPRINTK("%s", nodename);

	err = xenbus_probe_node(bus, type, nodename);
	kfree(nodename);
	return err;
}