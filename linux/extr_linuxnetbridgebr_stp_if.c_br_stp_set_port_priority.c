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
struct net_bridge_port {unsigned long priority; TYPE_1__* br; void* designated_port; void* port_id; int /*<<< orphan*/  designated_bridge; int /*<<< orphan*/  port_no; } ;
typedef  void* port_id ;
struct TYPE_2__ {int /*<<< orphan*/  bridge_id; } ;

/* Variables and functions */
 unsigned long BR_MAX_PORT_PRIORITY ; 
 int ERANGE ; 
 int /*<<< orphan*/  br_become_designated_port (struct net_bridge_port*) ; 
 scalar_t__ br_is_designated_port (struct net_bridge_port*) ; 
 void* br_make_port_id (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_port_state_selection (TYPE_1__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int br_stp_set_port_priority(struct net_bridge_port *p, unsigned long newprio)
{
	port_id new_port_id;

	if (newprio > BR_MAX_PORT_PRIORITY)
		return -ERANGE;

	new_port_id = br_make_port_id(newprio, p->port_no);
	if (br_is_designated_port(p))
		p->designated_port = new_port_id;

	p->port_id = new_port_id;
	p->priority = newprio;
	if (!memcmp(&p->br->bridge_id, &p->designated_bridge, 8) &&
	    p->port_id < p->designated_port) {
		br_become_designated_port(p);
		br_port_state_selection(p->br);
	}

	return 0;
}