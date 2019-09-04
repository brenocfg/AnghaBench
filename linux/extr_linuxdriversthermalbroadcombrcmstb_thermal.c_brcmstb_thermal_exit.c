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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct brcmstb_thermal_priv {struct thermal_zone_device* thermal; } ;

/* Variables and functions */
 struct brcmstb_thermal_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  thermal_zone_of_sensor_unregister (int /*<<< orphan*/ *,struct thermal_zone_device*) ; 

__attribute__((used)) static int brcmstb_thermal_exit(struct platform_device *pdev)
{
	struct brcmstb_thermal_priv *priv = platform_get_drvdata(pdev);
	struct thermal_zone_device *thermal = priv->thermal;

	if (thermal)
		thermal_zone_of_sensor_unregister(&pdev->dev, priv->thermal);

	return 0;
}