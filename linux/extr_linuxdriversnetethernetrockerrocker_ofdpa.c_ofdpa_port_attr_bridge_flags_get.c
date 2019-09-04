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
struct rocker_port {struct ofdpa_port* wpriv; } ;
struct ofdpa_port {unsigned long brport_flags; } ;

/* Variables and functions */

__attribute__((used)) static int
ofdpa_port_attr_bridge_flags_get(const struct rocker_port *rocker_port,
				 unsigned long *p_brport_flags)
{
	const struct ofdpa_port *ofdpa_port = rocker_port->wpriv;

	*p_brport_flags = ofdpa_port->brport_flags;
	return 0;
}