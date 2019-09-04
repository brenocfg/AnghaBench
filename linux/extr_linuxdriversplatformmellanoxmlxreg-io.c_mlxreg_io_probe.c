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
struct mlxreg_io_priv_data {int /*<<< orphan*/  hwmon; int /*<<< orphan*/  groups; struct platform_device* pdev; int /*<<< orphan*/  pdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct mlxreg_io_priv_data*) ; 
 int /*<<< orphan*/  devm_hwmon_device_register_with_groups (int /*<<< orphan*/ *,char*,struct mlxreg_io_priv_data*,int /*<<< orphan*/ ) ; 
 struct mlxreg_io_priv_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int mlxreg_io_attr_init (struct mlxreg_io_priv_data*) ; 

__attribute__((used)) static int mlxreg_io_probe(struct platform_device *pdev)
{
	struct mlxreg_io_priv_data *priv;
	int err;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->pdata = dev_get_platdata(&pdev->dev);
	if (!priv->pdata) {
		dev_err(&pdev->dev, "Failed to get platform data.\n");
		return -EINVAL;
	}

	priv->pdev = pdev;

	err = mlxreg_io_attr_init(priv);
	if (err) {
		dev_err(&priv->pdev->dev, "Failed to allocate attributes: %d\n",
			err);
		return err;
	}

	priv->hwmon = devm_hwmon_device_register_with_groups(&pdev->dev,
							     "mlxreg_io",
							      priv,
							      priv->groups);
	if (IS_ERR(priv->hwmon)) {
		dev_err(&pdev->dev, "Failed to register hwmon device %ld\n",
			PTR_ERR(priv->hwmon));
		return PTR_ERR(priv->hwmon);
	}

	dev_set_drvdata(&pdev->dev, priv);

	return 0;
}