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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {struct imx_pwm_data* data; } ;
struct imx_pwm_data {scalar_t__ polarity_supported; int /*<<< orphan*/  ops; } ;
struct TYPE_2__ {int base; int npwm; int of_pwm_n_cells; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * dev; int /*<<< orphan*/  ops; } ;
struct imx_chip {TYPE_1__ chip; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  clk_per; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct imx_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_pwm_dt_ids ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx_chip*) ; 
 int pwmchip_add (TYPE_1__*) ; 

__attribute__((used)) static int imx_pwm_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id =
			of_match_device(imx_pwm_dt_ids, &pdev->dev);
	const struct imx_pwm_data *data;
	struct imx_chip *imx;
	struct resource *r;
	int ret = 0;

	if (!of_id)
		return -ENODEV;

	data = of_id->data;

	imx = devm_kzalloc(&pdev->dev, sizeof(*imx), GFP_KERNEL);
	if (imx == NULL)
		return -ENOMEM;

	imx->clk_per = devm_clk_get(&pdev->dev, "per");
	if (IS_ERR(imx->clk_per)) {
		dev_err(&pdev->dev, "getting per clock failed with %ld\n",
				PTR_ERR(imx->clk_per));
		return PTR_ERR(imx->clk_per);
	}

	imx->chip.ops = data->ops;
	imx->chip.dev = &pdev->dev;
	imx->chip.base = -1;
	imx->chip.npwm = 1;

	if (data->polarity_supported) {
		dev_dbg(&pdev->dev, "PWM supports output inversion\n");
		imx->chip.of_xlate = of_pwm_xlate_with_flags;
		imx->chip.of_pwm_n_cells = 3;
	}

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	imx->mmio_base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(imx->mmio_base))
		return PTR_ERR(imx->mmio_base);

	ret = pwmchip_add(&imx->chip);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, imx);
	return 0;
}