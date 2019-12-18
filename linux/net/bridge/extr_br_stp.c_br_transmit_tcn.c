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
struct net_bridge_port {int dummy; } ;
struct net_bridge {int /*<<< orphan*/  root_port; } ;

/* Variables and functions */
 struct net_bridge_port* br_get_port (struct net_bridge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_notice (struct net_bridge*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_send_tcn_bpdu (struct net_bridge_port*) ; 

void br_transmit_tcn(struct net_bridge *br)
{
	struct net_bridge_port *p;

	p = br_get_port(br, br->root_port);
	if (p)
		br_send_tcn_bpdu(p);
	else
		br_notice(br, "root port %u not found for topology notice\n",
			  br->root_port);
}