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
struct TYPE_2__ {int of_pwm_n_cells; int base; int /*<<< orphan*/  npwm; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct tpu_device {struct platform_device* pdev; TYPE_1__ chip; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; int /*<<< orphan*/  lock; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPU_CHANNEL_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct tpu_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tpu_device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpu_pwm_ops ; 

__attribute__((used)) static int tpu_probe(struct platform_device *pdev)
{
	struct tpu_device *tpu;
	struct resource *res;
	int ret;

	tpu = devm_kzalloc(&pdev->dev, sizeof(*tpu), GFP_KERNEL);
	if (tpu == NULL)
		return -ENOMEM;

	spin_lock_init(&tpu->lock);
	tpu->pdev = pdev;

	/* Map memory, get clock and pin control. */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	tpu->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(tpu->base))
		return PTR_ERR(tpu->base);

	tpu->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(tpu->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		return PTR_ERR(tpu->clk);
	}

	/* Initialize and register the device. */
	platform_set_drvdata(pdev, tpu);

	tpu->chip.dev = &pdev->dev;
	tpu->chip.ops = &tpu_pwm_ops;
	tpu->chip.of_xlate = of_pwm_xlate_with_flags;
	tpu->chip.of_pwm_n_cells = 3;
	tpu->chip.base = -1;
	tpu->chip.npwm = TPU_CHANNEL_MAX;

	ret = pwmchip_add(&tpu->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to register PWM chip\n");
		return ret;
	}

	dev_info(&pdev->dev, "TPU PWM %d registered\n", tpu->pdev->id);

	pm_runtime_enable(&pdev->dev);

	return 0;
}