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
struct knav_reg_acc_command {int command; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdsp; } ;
struct knav_range_info {TYPE_1__ acc_info; struct knav_acc_channel* acc; } ;
struct knav_device {int /*<<< orphan*/  dev; } ;
struct knav_acc_channel {int /*<<< orphan*/  name; } ;
typedef  enum knav_acc_result { ____Placeholder_knav_acc_result } knav_acc_result ;

/* Variables and functions */
 int ACC_CMD_DISABLE_CHANNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knav_acc_result_str (int) ; 
 int /*<<< orphan*/  knav_acc_setup_cmd (struct knav_device*,struct knav_range_info*,struct knav_reg_acc_command*,int) ; 
 int knav_acc_write (struct knav_device*,int /*<<< orphan*/ ,struct knav_reg_acc_command*) ; 

__attribute__((used)) static void knav_acc_stop(struct knav_device *kdev,
				struct knav_range_info *range,
				int queue)
{
	struct knav_reg_acc_command cmd;
	struct knav_acc_channel *acc;
	enum knav_acc_result result;

	acc = range->acc + queue;

	knav_acc_setup_cmd(kdev, range, &cmd, queue);
	cmd.command |= ACC_CMD_DISABLE_CHANNEL << 8;
	result = knav_acc_write(kdev, range->acc_info.pdsp, &cmd);

	dev_dbg(kdev->dev, "stopped acc channel %s, result %s\n",
		acc->name, knav_acc_result_str(result));
}