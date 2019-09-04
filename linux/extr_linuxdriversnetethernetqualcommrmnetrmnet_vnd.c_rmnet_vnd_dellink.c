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
typedef  scalar_t__ u8 ;
struct rmnet_port {int /*<<< orphan*/  nr_rmnet_devs; } ;
struct rmnet_endpoint {int /*<<< orphan*/ * egress_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RMNET_MAX_LOGICAL_EP ; 

int rmnet_vnd_dellink(u8 id, struct rmnet_port *port,
		      struct rmnet_endpoint *ep)
{
	if (id >= RMNET_MAX_LOGICAL_EP || !ep->egress_dev)
		return -EINVAL;

	ep->egress_dev = NULL;
	port->nr_rmnet_devs--;
	return 0;
}