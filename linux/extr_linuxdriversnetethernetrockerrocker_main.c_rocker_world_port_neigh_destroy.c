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
struct rocker_world_ops {int (* port_neigh_destroy ) (struct rocker_port*,struct neighbour*) ;} ;
struct rocker_port {TYPE_1__* rocker; } ;
struct neighbour {int dummy; } ;
struct TYPE_2__ {struct rocker_world_ops* wops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct rocker_port*,struct neighbour*) ; 

__attribute__((used)) static int rocker_world_port_neigh_destroy(struct rocker_port *rocker_port,
					   struct neighbour *n)
{
	struct rocker_world_ops *wops = rocker_port->rocker->wops;

	if (!wops->port_neigh_destroy)
		return -EOPNOTSUPP;
	return wops->port_neigh_destroy(rocker_port, n);
}