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
struct tcpm_port {int attached; scalar_t__ cc2; int pd_capable; int send_discover; int /*<<< orphan*/ * partner; } ;

/* Variables and functions */
 scalar_t__ TYPEC_CC_OPEN ; 
 int /*<<< orphan*/  TYPEC_DEVICE ; 
 int /*<<< orphan*/  TYPEC_POLARITY_CC1 ; 
 int /*<<< orphan*/  TYPEC_POLARITY_CC2 ; 
 int /*<<< orphan*/  TYPEC_SINK ; 
 int tcpm_set_polarity (struct tcpm_port*,int /*<<< orphan*/ ) ; 
 int tcpm_set_roles (struct tcpm_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcpm_snk_attach(struct tcpm_port *port)
{
	int ret;

	if (port->attached)
		return 0;

	ret = tcpm_set_polarity(port, port->cc2 != TYPEC_CC_OPEN ?
				TYPEC_POLARITY_CC2 : TYPEC_POLARITY_CC1);
	if (ret < 0)
		return ret;

	ret = tcpm_set_roles(port, true, TYPEC_SINK, TYPEC_DEVICE);
	if (ret < 0)
		return ret;

	port->pd_capable = false;

	port->partner = NULL;

	port->attached = true;
	port->send_discover = true;

	return 0;
}