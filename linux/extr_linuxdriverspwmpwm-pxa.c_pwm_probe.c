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
struct resource {int dummy; } ;
struct TYPE_2__ {int base; int npwm; int of_pwm_n_cells; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct pxa_pwm_chip {TYPE_1__ chip; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  clk; } ;
struct platform_device_id {int driver_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HAS_SECONDARY_PWM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct pxa_pwm_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pxa_pwm_chip*) ; 
 int pwmchip_add (TYPE_1__*) ; 
 struct platform_device_id* pxa_pwm_get_id_dt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxa_pwm_of_xlate ; 
 int /*<<< orphan*/  pxa_pwm_ops ; 

__attribute__((used)) static int pwm_probe(struct platform_device *pdev)
{
	const struct platform_device_id *id = platform_get_device_id(pdev);
	struct pxa_pwm_chip *pwm;
	struct resource *r;
	int ret = 0;

	if (IS_ENABLED(CONFIG_OF) && id == NULL)
		id = pxa_pwm_get_id_dt(&pdev->dev);

	if (id == NULL)
		return -EINVAL;

	pwm = devm_kzalloc(&pdev->dev, sizeof(*pwm), GFP_KERNEL);
	if (pwm == NULL)
		return -ENOMEM;

	pwm->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(pwm->clk))
		return PTR_ERR(pwm->clk);

	pwm->chip.dev = &pdev->dev;
	pwm->chip.ops = &pxa_pwm_ops;
	pwm->chip.base = -1;
	pwm->chip.npwm = (id->driver_data & HAS_SECONDARY_PWM) ? 2 : 1;

	if (IS_ENABLED(CONFIG_OF)) {
		pwm->chip.of_xlate = pxa_pwm_of_xlate;
		pwm->chip.of_pwm_n_cells = 1;
	}

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pwm->mmio_base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(pwm->mmio_base))
		return PTR_ERR(pwm->mmio_base);

	ret = pwmchip_add(&pwm->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, pwm);
	return 0;
}