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
struct dsa_switch_tree {struct dsa_switch** ds; } ;
struct dsa_switch {int num_ports; struct dsa_port* ports; } ;
struct dsa_port {struct device_node* dn; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int DSA_MAX_SWITCHES ; 

__attribute__((used)) static struct dsa_port *dsa_tree_find_port_by_node(struct dsa_switch_tree *dst,
						   struct device_node *dn)
{
	struct dsa_switch *ds;
	struct dsa_port *dp;
	int device, port;

	for (device = 0; device < DSA_MAX_SWITCHES; device++) {
		ds = dst->ds[device];
		if (!ds)
			continue;

		for (port = 0; port < ds->num_ports; port++) {
			dp = &ds->ports[port];

			if (dp->dn == dn)
				return dp;
		}
	}

	return NULL;
}