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
struct tcmu_dev {unsigned int qfull_time_out; int cmd_time_out; int /*<<< orphan*/  name; int /*<<< orphan*/  qfull_queue; int /*<<< orphan*/  qfull_timer; } ;
struct tcmu_cmd {int /*<<< orphan*/  cmd_id; int /*<<< orphan*/  queue_entry; struct tcmu_dev* tcmu_dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned int TCMU_TIME_OUT ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tcmu_setup_cmd_timer (struct tcmu_cmd*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_to_qfull_queue(struct tcmu_cmd *tcmu_cmd)
{
	struct tcmu_dev *udev = tcmu_cmd->tcmu_dev;
	unsigned int tmo;
	int ret;

	/*
	 * For backwards compat if qfull_time_out is not set use
	 * cmd_time_out and if that's not set use the default time out.
	 */
	if (!udev->qfull_time_out)
		return -ETIMEDOUT;
	else if (udev->qfull_time_out > 0)
		tmo = udev->qfull_time_out;
	else if (udev->cmd_time_out)
		tmo = udev->cmd_time_out;
	else
		tmo = TCMU_TIME_OUT;

	ret = tcmu_setup_cmd_timer(tcmu_cmd, tmo, &udev->qfull_timer);
	if (ret)
		return ret;

	list_add_tail(&tcmu_cmd->queue_entry, &udev->qfull_queue);
	pr_debug("adding cmd %u on dev %s to ring space wait queue\n",
		 tcmu_cmd->cmd_id, udev->name);
	return 0;
}