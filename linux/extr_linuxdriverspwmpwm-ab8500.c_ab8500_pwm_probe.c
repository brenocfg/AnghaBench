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
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int npwm; int /*<<< orphan*/  base; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct ab8500_pwm_chip {TYPE_1__ chip; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ab8500_pwm_ops ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct ab8500_pwm_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ab8500_pwm_chip*) ; 
 int pwmchip_add (TYPE_1__*) ; 

__attribute__((used)) static int ab8500_pwm_probe(struct platform_device *pdev)
{
	struct ab8500_pwm_chip *ab8500;
	int err;

	/*
	 * Nothing to be done in probe, this is required to get the
	 * device which is required for ab8500 read and write
	 */
	ab8500 = devm_kzalloc(&pdev->dev, sizeof(*ab8500), GFP_KERNEL);
	if (ab8500 == NULL)
		return -ENOMEM;

	ab8500->chip.dev = &pdev->dev;
	ab8500->chip.ops = &ab8500_pwm_ops;
	ab8500->chip.base = pdev->id;
	ab8500->chip.npwm = 1;

	err = pwmchip_add(&ab8500->chip);
	if (err < 0)
		return err;

	dev_dbg(&pdev->dev, "pwm probe successful\n");
	platform_set_drvdata(pdev, ab8500);

	return 0;
}