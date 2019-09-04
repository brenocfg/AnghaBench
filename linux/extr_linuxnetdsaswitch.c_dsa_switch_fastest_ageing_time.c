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
struct dsa_switch {int num_ports; struct dsa_port* ports; } ;
struct dsa_port {unsigned int ageing_time; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int dsa_switch_fastest_ageing_time(struct dsa_switch *ds,
						   unsigned int ageing_time)
{
	int i;

	for (i = 0; i < ds->num_ports; ++i) {
		struct dsa_port *dp = &ds->ports[i];

		if (dp->ageing_time && dp->ageing_time < ageing_time)
			ageing_time = dp->ageing_time;
	}

	return ageing_time;
}