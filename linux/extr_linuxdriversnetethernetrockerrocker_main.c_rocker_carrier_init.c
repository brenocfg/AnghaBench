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
typedef  int u64 ;
struct rocker_port {int pport; int /*<<< orphan*/  dev; struct rocker* rocker; } ;
struct rocker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_PHYS_LINK_STATUS ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int rocker_read64 (struct rocker const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rocker_carrier_init(const struct rocker_port *rocker_port)
{
	const struct rocker *rocker = rocker_port->rocker;
	u64 link_status = rocker_read64(rocker, PORT_PHYS_LINK_STATUS);
	bool link_up;

	link_up = link_status & (1 << rocker_port->pport);
	if (link_up)
		netif_carrier_on(rocker_port->dev);
	else
		netif_carrier_off(rocker_port->dev);
}