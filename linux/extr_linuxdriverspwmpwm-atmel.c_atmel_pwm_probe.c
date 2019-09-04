#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_7__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct atmel_pwm_registers {int dummy; } ;
struct TYPE_6__ {int of_pwm_n_cells; int base; int npwm; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; TYPE_2__* dev; } ;
struct atmel_pwm_chip {int /*<<< orphan*/  clk; TYPE_1__ chip; int /*<<< orphan*/  isr_lock; scalar_t__ updated_pwms; struct atmel_pwm_registers const* regs; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct atmel_pwm_registers* atmel_pwm_get_driver_data (struct platform_device*) ; 
 int /*<<< orphan*/  atmel_pwm_ops ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct atmel_pwm_chip* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct atmel_pwm_chip*) ; 
 int pwmchip_add (TYPE_1__*) ; 

__attribute__((used)) static int atmel_pwm_probe(struct platform_device *pdev)
{
	const struct atmel_pwm_registers *regs;
	struct atmel_pwm_chip *atmel_pwm;
	struct resource *res;
	int ret;

	regs = atmel_pwm_get_driver_data(pdev);
	if (!regs)
		return -ENODEV;

	atmel_pwm = devm_kzalloc(&pdev->dev, sizeof(*atmel_pwm), GFP_KERNEL);
	if (!atmel_pwm)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	atmel_pwm->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(atmel_pwm->base))
		return PTR_ERR(atmel_pwm->base);

	atmel_pwm->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(atmel_pwm->clk))
		return PTR_ERR(atmel_pwm->clk);

	ret = clk_prepare(atmel_pwm->clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to prepare PWM clock\n");
		return ret;
	}

	atmel_pwm->chip.dev = &pdev->dev;
	atmel_pwm->chip.ops = &atmel_pwm_ops;

	if (pdev->dev.of_node) {
		atmel_pwm->chip.of_xlate = of_pwm_xlate_with_flags;
		atmel_pwm->chip.of_pwm_n_cells = 3;
	}

	atmel_pwm->chip.base = -1;
	atmel_pwm->chip.npwm = 4;
	atmel_pwm->regs = regs;
	atmel_pwm->updated_pwms = 0;
	mutex_init(&atmel_pwm->isr_lock);

	ret = pwmchip_add(&atmel_pwm->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to add PWM chip %d\n", ret);
		goto unprepare_clk;
	}

	platform_set_drvdata(pdev, atmel_pwm);

	return ret;

unprepare_clk:
	clk_unprepare(atmel_pwm->clk);
	return ret;
}