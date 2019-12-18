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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct lochnagar_sc_priv {int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct lochnagar_sc_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lochnagar_sc_dai ; 
 int /*<<< orphan*/  lochnagar_sc_driver ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lochnagar_sc_priv*) ; 

__attribute__((used)) static int lochnagar_sc_probe(struct platform_device *pdev)
{
	struct lochnagar_sc_priv *priv;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->mclk = devm_clk_get(&pdev->dev, "mclk");
	if (IS_ERR(priv->mclk)) {
		ret = PTR_ERR(priv->mclk);
		dev_err(&pdev->dev, "Failed to get MCLK: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, priv);

	return devm_snd_soc_register_component(&pdev->dev,
					       &lochnagar_sc_driver,
					       lochnagar_sc_dai,
					       ARRAY_SIZE(lochnagar_sc_dai));
}