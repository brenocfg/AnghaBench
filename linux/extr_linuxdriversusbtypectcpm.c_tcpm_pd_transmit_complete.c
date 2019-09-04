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
struct tcpm_port {int tx_status; int /*<<< orphan*/  tx_complete; } ;
typedef  enum tcpm_transmit_status { ____Placeholder_tcpm_transmit_status } tcpm_transmit_status ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,int) ; 

void tcpm_pd_transmit_complete(struct tcpm_port *port,
			       enum tcpm_transmit_status status)
{
	tcpm_log(port, "PD TX complete, status: %u", status);
	port->tx_status = status;
	complete(&port->tx_complete);
}