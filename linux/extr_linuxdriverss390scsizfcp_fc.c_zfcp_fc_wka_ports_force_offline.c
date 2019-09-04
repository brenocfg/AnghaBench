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
struct zfcp_fc_wka_ports {int /*<<< orphan*/  as; int /*<<< orphan*/  ds; int /*<<< orphan*/  ts; int /*<<< orphan*/  ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_fc_wka_port_force_offline (int /*<<< orphan*/ *) ; 

void zfcp_fc_wka_ports_force_offline(struct zfcp_fc_wka_ports *gs)
{
	if (!gs)
		return;
	zfcp_fc_wka_port_force_offline(&gs->ms);
	zfcp_fc_wka_port_force_offline(&gs->ts);
	zfcp_fc_wka_port_force_offline(&gs->ds);
	zfcp_fc_wka_port_force_offline(&gs->as);
}