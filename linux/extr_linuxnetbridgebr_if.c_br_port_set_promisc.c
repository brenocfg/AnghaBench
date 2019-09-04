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
struct net_bridge_port {int /*<<< orphan*/  flags; int /*<<< orphan*/  br; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_PROMISC ; 
 int /*<<< orphan*/  br_fdb_unsync_static (int /*<<< orphan*/ ,struct net_bridge_port*) ; 
 scalar_t__ br_promisc_port (struct net_bridge_port*) ; 
 int dev_set_promiscuity (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void br_port_set_promisc(struct net_bridge_port *p)
{
	int err = 0;

	if (br_promisc_port(p))
		return;

	err = dev_set_promiscuity(p->dev, 1);
	if (err)
		return;

	br_fdb_unsync_static(p->br, p);
	p->flags |= BR_PROMISC;
}