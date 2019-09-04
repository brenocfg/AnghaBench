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
struct TYPE_2__ {int base; int npwm; int of_pwm_n_cells; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; } ;
struct clps711x_chip {TYPE_1__ chip; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; int /*<<< orphan*/  pmpcon; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clps711x_pwm_ops ; 
 int /*<<< orphan*/  clps711x_pwm_xlate ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct clps711x_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct clps711x_chip*) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clps711x_pwm_probe(struct platform_device *pdev)
{
	struct clps711x_chip *priv;
	struct resource *res;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->pmpcon = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->pmpcon))
		return PTR_ERR(priv->pmpcon);

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);

	priv->chip.ops = &clps711x_pwm_ops;
	priv->chip.dev = &pdev->dev;
	priv->chip.base = -1;
	priv->chip.npwm = 2;
	priv->chip.of_xlate = clps711x_pwm_xlate;
	priv->chip.of_pwm_n_cells = 1;

	spin_lock_init(&priv->lock);

	platform_set_drvdata(pdev, priv);

	return pwmchip_add(&priv->chip);
}