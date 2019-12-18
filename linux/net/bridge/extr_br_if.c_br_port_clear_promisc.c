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
struct net_bridge_port {int /*<<< orphan*/  flags; TYPE_1__* dev; int /*<<< orphan*/  br; } ;
struct TYPE_2__ {int priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_PROMISC ; 
 int IFF_UNICAST_FLT ; 
 int br_fdb_sync_static (int /*<<< orphan*/ ,struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_promisc_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  dev_set_promiscuity (TYPE_1__*,int) ; 

__attribute__((used)) static void br_port_clear_promisc(struct net_bridge_port *p)
{
	int err;

	/* Check if the port is already non-promisc or if it doesn't
	 * support UNICAST filtering.  Without unicast filtering support
	 * we'll end up re-enabling promisc mode anyway, so just check for
	 * it here.
	 */
	if (!br_promisc_port(p) || !(p->dev->priv_flags & IFF_UNICAST_FLT))
		return;

	/* Since we'll be clearing the promisc mode, program the port
	 * first so that we don't have interruption in traffic.
	 */
	err = br_fdb_sync_static(p->br, p);
	if (err)
		return;

	dev_set_promiscuity(p->dev, -1);
	p->flags &= ~BR_PROMISC;
}