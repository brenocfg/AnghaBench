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
struct thermal_zone_device {int dummy; } ;
struct tango_thermal_priv {int /*<<< orphan*/  thresh_idx; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IDX_MIN ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct tango_thermal_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct thermal_zone_device* devm_thermal_zone_of_sensor_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tango_thermal_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ops ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tango_thermal_priv*) ; 
 int /*<<< orphan*/  tango_thermal_init (struct tango_thermal_priv*) ; 

__attribute__((used)) static int tango_thermal_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct tango_thermal_priv *priv;
	struct thermal_zone_device *tzdev;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	platform_set_drvdata(pdev, priv);
	priv->thresh_idx = IDX_MIN;
	tango_thermal_init(priv);

	tzdev = devm_thermal_zone_of_sensor_register(&pdev->dev, 0, priv, &ops);
	return PTR_ERR_OR_ZERO(tzdev);
}