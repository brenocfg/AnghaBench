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
struct dsa_switch {int num_ports; int /*<<< orphan*/ * ports; } ;

/* Variables and functions */
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,int) ; 
 scalar_t__ dsa_is_dsa_port (struct dsa_switch*,int) ; 
 int dsa_port_link_register_of (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dsa_cpu_dsa_setups(struct dsa_switch *ds)
{
	int ret, port;

	for (port = 0; port < ds->num_ports; port++) {
		if (!(dsa_is_cpu_port(ds, port) || dsa_is_dsa_port(ds, port)))
			continue;

		ret = dsa_port_link_register_of(&ds->ports[port]);
		if (ret)
			return ret;
	}
	return 0;
}