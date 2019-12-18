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
struct softnet_data {struct softnet_data* rps_ipi_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  net_rps_send_ipi (struct softnet_data*) ; 

__attribute__((used)) static void net_rps_action_and_irq_enable(struct softnet_data *sd)
{
#ifdef CONFIG_RPS
	struct softnet_data *remsd = sd->rps_ipi_list;

	if (remsd) {
		sd->rps_ipi_list = NULL;

		local_irq_enable();

		/* Send pending IPI's to kick RPS processing on remote cpus. */
		net_rps_send_ipi(remsd);
	} else
#endif
		local_irq_enable();
}