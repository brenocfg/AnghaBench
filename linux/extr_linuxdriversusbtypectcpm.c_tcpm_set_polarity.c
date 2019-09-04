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
struct tcpm_port {int polarity; TYPE_1__* tcpc; } ;
typedef  enum typec_cc_polarity { ____Placeholder_typec_cc_polarity } typec_cc_polarity ;
struct TYPE_2__ {int (* set_polarity ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,int) ; 

__attribute__((used)) static int tcpm_set_polarity(struct tcpm_port *port,
			     enum typec_cc_polarity polarity)
{
	int ret;

	tcpm_log(port, "polarity %d", polarity);

	ret = port->tcpc->set_polarity(port->tcpc, polarity);
	if (ret < 0)
		return ret;

	port->polarity = polarity;

	return 0;
}