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
struct net_bridge_port {int /*<<< orphan*/  br; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_fdb_unsync_static (int /*<<< orphan*/ ,struct net_bridge_port*) ; 
 scalar_t__ br_promisc_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  dev_set_allmulti (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_set_promiscuity (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nbp_delete_promisc(struct net_bridge_port *p)
{
	/* If port is currently promiscuous, unset promiscuity.
	 * Otherwise, it is a static port so remove all addresses
	 * from it.
	 */
	dev_set_allmulti(p->dev, -1);
	if (br_promisc_port(p))
		dev_set_promiscuity(p->dev, -1);
	else
		br_fdb_unsync_static(p->br, p);
}