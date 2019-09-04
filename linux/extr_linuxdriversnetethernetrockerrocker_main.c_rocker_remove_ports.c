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
struct rocker_port {int /*<<< orphan*/  dev; } ;
struct rocker {int port_count; struct rocker_port** ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rocker_port**) ; 
 int /*<<< orphan*/  rocker_world_fini (struct rocker*) ; 
 int /*<<< orphan*/  rocker_world_port_fini (struct rocker_port*) ; 
 int /*<<< orphan*/  rocker_world_port_post_fini (struct rocker_port*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rocker_remove_ports(struct rocker *rocker)
{
	struct rocker_port *rocker_port;
	int i;

	for (i = 0; i < rocker->port_count; i++) {
		rocker_port = rocker->ports[i];
		if (!rocker_port)
			continue;
		rocker_world_port_fini(rocker_port);
		unregister_netdev(rocker_port->dev);
		rocker_world_port_post_fini(rocker_port);
		free_netdev(rocker_port->dev);
	}
	rocker_world_fini(rocker);
	kfree(rocker->ports);
}