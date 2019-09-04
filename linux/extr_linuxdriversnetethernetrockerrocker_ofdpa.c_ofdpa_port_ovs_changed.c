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
struct ofdpa_port {struct net_device* bridge_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ofdpa_port_fwd_disable (struct ofdpa_port*,int /*<<< orphan*/ ) ; 
 int ofdpa_port_fwd_enable (struct ofdpa_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_ovs_changed(struct ofdpa_port *ofdpa_port,
				  struct net_device *master)
{
	int err;

	ofdpa_port->bridge_dev = master;

	err = ofdpa_port_fwd_disable(ofdpa_port, 0);
	if (err)
		return err;
	err = ofdpa_port_fwd_enable(ofdpa_port, 0);

	return err;
}