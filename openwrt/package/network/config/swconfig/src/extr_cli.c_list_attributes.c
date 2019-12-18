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
struct switch_dev {char* dev_name; char* alias; char* name; int ports; int cpu_port; int vlans; int /*<<< orphan*/  port_ops; int /*<<< orphan*/  vlan_ops; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_attrs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
list_attributes(struct switch_dev *dev)
{
	printf("%s: %s(%s), ports: %d (cpu @ %d), vlans: %d\n", dev->dev_name, dev->alias, dev->name, dev->ports, dev->cpu_port, dev->vlans);
	printf("     --switch\n");
	print_attrs(dev->ops);
	printf("     --vlan\n");
	print_attrs(dev->vlan_ops);
	printf("     --port\n");
	print_attrs(dev->port_ops);
}