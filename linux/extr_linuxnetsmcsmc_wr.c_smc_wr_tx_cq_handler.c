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
struct smc_ib_device {int /*<<< orphan*/  send_tasklet; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void smc_wr_tx_cq_handler(struct ib_cq *ib_cq, void *cq_context)
{
	struct smc_ib_device *dev = (struct smc_ib_device *)cq_context;

	tasklet_schedule(&dev->send_tasklet);
}