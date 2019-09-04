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
struct TYPE_2__ {int calibrate; } ;
struct ab8500_fg {int calib_state; int /*<<< orphan*/  fg_periodic_work; int /*<<< orphan*/  fg_wq; TYPE_1__ flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AB8500_FG_CALIB_END 130 
#define  AB8500_FG_CALIB_INIT 129 
#define  AB8500_FG_CALIB_WAIT 128 
 int /*<<< orphan*/  AB8500_GASG_CC_CTRL_REG ; 
 int /*<<< orphan*/  AB8500_GAS_GAUGE ; 
 int /*<<< orphan*/  CC_INTAVGOFFSET_ENA ; 
 int /*<<< orphan*/  CC_INT_CAL_N_AVG_MASK ; 
 int /*<<< orphan*/  CC_INT_CAL_SAMPLES_8 ; 
 int /*<<< orphan*/  CC_MUXOFFSET ; 
 int abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ab8500_fg_algorithm_calibrate(struct ab8500_fg *di)
{
	int ret;

	switch (di->calib_state) {
	case AB8500_FG_CALIB_INIT:
		dev_dbg(di->dev, "Calibration ongoing...\n");

		ret = abx500_mask_and_set_register_interruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_CTRL_REG,
			CC_INT_CAL_N_AVG_MASK, CC_INT_CAL_SAMPLES_8);
		if (ret < 0)
			goto err;

		ret = abx500_mask_and_set_register_interruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_CTRL_REG,
			CC_INTAVGOFFSET_ENA, CC_INTAVGOFFSET_ENA);
		if (ret < 0)
			goto err;
		di->calib_state = AB8500_FG_CALIB_WAIT;
		break;
	case AB8500_FG_CALIB_END:
		ret = abx500_mask_and_set_register_interruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_CTRL_REG,
			CC_MUXOFFSET, CC_MUXOFFSET);
		if (ret < 0)
			goto err;
		di->flags.calibrate = false;
		dev_dbg(di->dev, "Calibration done...\n");
		queue_delayed_work(di->fg_wq, &di->fg_periodic_work, 0);
		break;
	case AB8500_FG_CALIB_WAIT:
		dev_dbg(di->dev, "Calibration WFI\n");
	default:
		break;
	}
	return;
err:
	/* Something went wrong, don't calibrate then */
	dev_err(di->dev, "failed to calibrate the CC\n");
	di->flags.calibrate = false;
	di->calib_state = AB8500_FG_CALIB_INIT;
	queue_delayed_work(di->fg_wq, &di->fg_periodic_work, 0);
}