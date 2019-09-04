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
struct pwm_device {int dummy; } ;
struct pwm_chip {TYPE_1__* ops; struct device* dev; } ;
struct meson_pwm_channel {int /*<<< orphan*/  state; scalar_t__ clk; scalar_t__ clk_parent; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_state ) (struct pwm_chip*,struct pwm_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  __clk_get_name (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int clk_set_parent (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int,...) ; 
 struct meson_pwm_channel* pwm_get_chip_data (struct pwm_device*) ; 
 int /*<<< orphan*/  stub1 (struct pwm_chip*,struct pwm_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meson_pwm_request(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct meson_pwm_channel *channel = pwm_get_chip_data(pwm);
	struct device *dev = chip->dev;
	int err;

	if (!channel)
		return -ENODEV;

	if (channel->clk_parent) {
		err = clk_set_parent(channel->clk, channel->clk_parent);
		if (err < 0) {
			dev_err(dev, "failed to set parent %s for %s: %d\n",
				__clk_get_name(channel->clk_parent),
				__clk_get_name(channel->clk), err);
				return err;
		}
	}

	err = clk_prepare_enable(channel->clk);
	if (err < 0) {
		dev_err(dev, "failed to enable clock %s: %d\n",
			__clk_get_name(channel->clk), err);
		return err;
	}

	chip->ops->get_state(chip, pwm, &channel->state);

	return 0;
}