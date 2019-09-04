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
typedef  scalar_t__ u16 ;
struct switchdev_obj_port_vlan {scalar_t__ vid_begin; scalar_t__ vid_end; int /*<<< orphan*/  flags; } ;
struct rocker_port {struct ofdpa_port* wpriv; } ;
struct ofdpa_port {int dummy; } ;

/* Variables and functions */
 int ofdpa_port_vlan_add (struct ofdpa_port*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_obj_vlan_add(struct rocker_port *rocker_port,
				   const struct switchdev_obj_port_vlan *vlan)
{
	struct ofdpa_port *ofdpa_port = rocker_port->wpriv;
	u16 vid;
	int err;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; vid++) {
		err = ofdpa_port_vlan_add(ofdpa_port, vid, vlan->flags);
		if (err)
			return err;
	}

	return 0;
}