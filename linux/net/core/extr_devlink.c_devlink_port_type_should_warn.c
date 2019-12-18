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
struct TYPE_2__ {scalar_t__ flavour; } ;
struct devlink_port {TYPE_1__ attrs; } ;

/* Variables and functions */
 scalar_t__ DEVLINK_PORT_FLAVOUR_CPU ; 
 scalar_t__ DEVLINK_PORT_FLAVOUR_DSA ; 

__attribute__((used)) static bool devlink_port_type_should_warn(struct devlink_port *devlink_port)
{
	/* Ignore CPU and DSA flavours. */
	return devlink_port->attrs.flavour != DEVLINK_PORT_FLAVOUR_CPU &&
	       devlink_port->attrs.flavour != DEVLINK_PORT_FLAVOUR_DSA;
}