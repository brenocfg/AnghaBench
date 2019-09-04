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
struct qcom_slim_ngd_ctrl {scalar_t__ state; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ QCOM_SLIM_NGD_CTRL_ASLEEP ; 
 scalar_t__ QCOM_SLIM_NGD_CTRL_AWAKE ; 
 scalar_t__ QCOM_SLIM_NGD_CTRL_DOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct qcom_slim_ngd_ctrl* dev_get_drvdata (struct device*) ; 
 int qcom_slim_ngd_power_up (struct qcom_slim_ngd_ctrl*) ; 

__attribute__((used)) static int qcom_slim_ngd_runtime_resume(struct device *dev)
{
	struct qcom_slim_ngd_ctrl *ctrl = dev_get_drvdata(dev);
	int ret = 0;

	if (ctrl->state >= QCOM_SLIM_NGD_CTRL_ASLEEP)
		ret = qcom_slim_ngd_power_up(ctrl);
	if (ret) {
		/* Did SSR cause this power up failure */
		if (ctrl->state != QCOM_SLIM_NGD_CTRL_DOWN)
			ctrl->state = QCOM_SLIM_NGD_CTRL_ASLEEP;
		else
			dev_err(ctrl->dev, "HW wakeup attempt during SSR\n");
	} else {
		ctrl->state = QCOM_SLIM_NGD_CTRL_AWAKE;
	}

	return 0;
}