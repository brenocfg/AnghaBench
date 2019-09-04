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
struct pwm_chip {int of_pwm_n_cells; int base; int npwm; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct cros_ec_pwm_device {struct cros_ec_device* ec; struct pwm_chip chip; } ;
struct cros_ec_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cros_ec_num_pwms (struct cros_ec_device*) ; 
 int /*<<< orphan*/  cros_ec_pwm_ops ; 
 int /*<<< orphan*/  cros_ec_pwm_xlate ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct cros_ec_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct cros_ec_pwm_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cros_ec_pwm_device*) ; 
 int pwmchip_add (struct pwm_chip*) ; 

__attribute__((used)) static int cros_ec_pwm_probe(struct platform_device *pdev)
{
	struct cros_ec_device *ec = dev_get_drvdata(pdev->dev.parent);
	struct device *dev = &pdev->dev;
	struct cros_ec_pwm_device *ec_pwm;
	struct pwm_chip *chip;
	int ret;

	if (!ec) {
		dev_err(dev, "no parent EC device\n");
		return -EINVAL;
	}

	ec_pwm = devm_kzalloc(dev, sizeof(*ec_pwm), GFP_KERNEL);
	if (!ec_pwm)
		return -ENOMEM;
	chip = &ec_pwm->chip;
	ec_pwm->ec = ec;

	/* PWM chip */
	chip->dev = dev;
	chip->ops = &cros_ec_pwm_ops;
	chip->of_xlate = cros_ec_pwm_xlate;
	chip->of_pwm_n_cells = 1;
	chip->base = -1;
	ret = cros_ec_num_pwms(ec);
	if (ret < 0) {
		dev_err(dev, "Couldn't find PWMs: %d\n", ret);
		return ret;
	}
	chip->npwm = ret;
	dev_dbg(dev, "Probed %u PWMs\n", chip->npwm);

	ret = pwmchip_add(chip);
	if (ret < 0) {
		dev_err(dev, "cannot register PWM: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, ec_pwm);

	return ret;
}