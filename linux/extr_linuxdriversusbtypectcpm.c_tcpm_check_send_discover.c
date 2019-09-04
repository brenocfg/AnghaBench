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
struct tcpm_port {scalar_t__ data_role; int send_discover; scalar_t__ pd_capable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DISCOVER_IDENT ; 
 scalar_t__ TYPEC_HOST ; 
 int /*<<< orphan*/  USB_SID_PD ; 
 int /*<<< orphan*/  tcpm_send_vdm (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcpm_check_send_discover(struct tcpm_port *port)
{
	if (port->data_role == TYPEC_HOST && port->send_discover &&
	    port->pd_capable) {
		tcpm_send_vdm(port, USB_SID_PD, CMD_DISCOVER_IDENT, NULL, 0);
		port->send_discover = false;
	}
}