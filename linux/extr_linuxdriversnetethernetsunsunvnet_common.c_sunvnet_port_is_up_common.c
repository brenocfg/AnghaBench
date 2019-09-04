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
struct vio_driver_state {int hs_state; } ;
struct vnet_port {struct vio_driver_state vio; } ;

/* Variables and functions */
 int VIO_HS_COMPLETE ; 

bool sunvnet_port_is_up_common(struct vnet_port *vnet)
{
	struct vio_driver_state *vio = &vnet->vio;

	return !!(vio->hs_state & VIO_HS_COMPLETE);
}