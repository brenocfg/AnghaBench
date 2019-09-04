#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vctrl_data {unsigned int sel; int min_slew_down_rate; TYPE_2__* vtable; int /*<<< orphan*/  ovp_threshold; struct regulator* ctrl_reg; } ;
struct regulator_dev {int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct regulator {int dummy; } ;
struct TYPE_4__ {unsigned int ovp_min_sel; int out; int /*<<< orphan*/  ctrl; } ;
struct TYPE_3__ {unsigned int n_voltages; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct vctrl_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int regulator_set_voltage (struct regulator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int vctrl_set_voltage_sel(struct regulator_dev *rdev,
				 unsigned int selector)
{
	struct vctrl_data *vctrl = rdev_get_drvdata(rdev);
	struct regulator *ctrl_reg = vctrl->ctrl_reg;
	unsigned int orig_sel = vctrl->sel;
	int ret;

	if (selector >= rdev->desc->n_voltages)
		return -EINVAL;

	if (selector >= vctrl->sel || !vctrl->ovp_threshold) {
		/* voltage rising or no OVP */
		ret = regulator_set_voltage(ctrl_reg,
					    vctrl->vtable[selector].ctrl,
					    vctrl->vtable[selector].ctrl);
		if (!ret)
			vctrl->sel = selector;

		return ret;
	}

	while (vctrl->sel != selector) {
		unsigned int next_sel;
		int delay;

		if (selector >= vctrl->vtable[vctrl->sel].ovp_min_sel)
			next_sel = selector;
		else
			next_sel = vctrl->vtable[vctrl->sel].ovp_min_sel;

		ret = regulator_set_voltage(ctrl_reg,
					    vctrl->vtable[next_sel].ctrl,
					    vctrl->vtable[next_sel].ctrl);
		if (ret) {
			dev_err(&rdev->dev,
				"failed to set control voltage to %duV\n",
				vctrl->vtable[next_sel].ctrl);
			goto err;
		}
		vctrl->sel = next_sel;

		delay = DIV_ROUND_UP(vctrl->vtable[vctrl->sel].out -
				     vctrl->vtable[next_sel].out,
				     vctrl->min_slew_down_rate);
		usleep_range(delay, delay + DIV_ROUND_UP(delay, 10));
	}

	return 0;

err:
	if (vctrl->sel != orig_sel) {
		/* Try to go back to original voltage */
		if (!regulator_set_voltage(ctrl_reg,
					   vctrl->vtable[orig_sel].ctrl,
					   vctrl->vtable[orig_sel].ctrl))
			vctrl->sel = orig_sel;
		else
			dev_warn(&rdev->dev,
				 "failed to restore original voltage\n");
	}

	return ret;
}