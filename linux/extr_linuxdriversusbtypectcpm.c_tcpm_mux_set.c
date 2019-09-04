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
struct tcpm_port {int /*<<< orphan*/  typec_port; scalar_t__ role_sw; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;
typedef  enum typec_orientation { ____Placeholder_typec_orientation } typec_orientation ;

/* Variables and functions */
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,int,int,int) ; 
 int typec_set_mode (int /*<<< orphan*/ ,int) ; 
 int typec_set_orientation (int /*<<< orphan*/ ,int) ; 
 int usb_role_switch_set_role (scalar_t__,int) ; 

__attribute__((used)) static int tcpm_mux_set(struct tcpm_port *port, int state,
			enum usb_role usb_role,
			enum typec_orientation orientation)
{
	int ret;

	tcpm_log(port, "Requesting mux state %d, usb-role %d, orientation %d",
		 state, usb_role, orientation);

	ret = typec_set_orientation(port->typec_port, orientation);
	if (ret)
		return ret;

	if (port->role_sw) {
		ret = usb_role_switch_set_role(port->role_sw, usb_role);
		if (ret)
			return ret;
	}

	return typec_set_mode(port->typec_port, state);
}