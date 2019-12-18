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
struct smc_ib_device {int /*<<< orphan*/  send_tasklet; int /*<<< orphan*/  recv_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void smc_wr_remove_dev(struct smc_ib_device *smcibdev)
{
	tasklet_kill(&smcibdev->recv_tasklet);
	tasklet_kill(&smcibdev->send_tasklet);
}