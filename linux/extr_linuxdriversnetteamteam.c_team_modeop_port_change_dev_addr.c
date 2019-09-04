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
struct team_port {int dummy; } ;
struct team {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  team_port_set_team_dev_addr (struct team*,struct team_port*) ; 

void team_modeop_port_change_dev_addr(struct team *team,
				      struct team_port *port)
{
	team_port_set_team_dev_addr(team, port);
}