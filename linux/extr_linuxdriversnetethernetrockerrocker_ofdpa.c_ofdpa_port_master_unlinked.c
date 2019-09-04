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
struct ofdpa_port {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ofdpa_port_bridge_leave (struct ofdpa_port*) ; 
 scalar_t__ ofdpa_port_is_bridged (struct ofdpa_port*) ; 
 scalar_t__ ofdpa_port_is_ovsed (struct ofdpa_port*) ; 
 int ofdpa_port_ovs_changed (struct ofdpa_port*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ofdpa_port_master_unlinked(struct rocker_port *rocker_port,
				      struct net_device *master)
{
	struct ofdpa_port *ofdpa_port = rocker_port->wpriv;
	int err = 0;

	if (ofdpa_port_is_bridged(ofdpa_port))
		err = ofdpa_port_bridge_leave(ofdpa_port);
	else if (ofdpa_port_is_ovsed(ofdpa_port))
		err = ofdpa_port_ovs_changed(ofdpa_port, NULL);
	return err;
}