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
struct vnet_port {int tso; scalar_t__ vsw; scalar_t__ tsolen; scalar_t__ rmtu; int /*<<< orphan*/  clean_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunvnet_port_free_tx_bufs_common (struct vnet_port*) ; 

void vnet_port_reset(struct vnet_port *port)
{
	del_timer(&port->clean_timer);
	sunvnet_port_free_tx_bufs_common(port);
	port->rmtu = 0;
	port->tso = (port->vsw == 0);  /* no tso in vsw, misbehaves in bridge */
	port->tsolen = 0;
}