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
struct xtfpga_i2s {scalar_t__ regmap; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  XTFPGA_I2S_CONFIG ; 
 int /*<<< orphan*/  XTFPGA_I2S_INT_MASK ; 
 int /*<<< orphan*/  XTFPGA_I2S_INT_STATUS ; 
 int /*<<< orphan*/  XTFPGA_I2S_INT_VALID ; 
 struct xtfpga_i2s* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtfpga_i2s_runtime_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xtfpga_i2s_remove(struct platform_device *pdev)
{
	struct xtfpga_i2s *i2s = dev_get_drvdata(&pdev->dev);

	if (i2s->regmap && !IS_ERR(i2s->regmap)) {
		regmap_write(i2s->regmap, XTFPGA_I2S_CONFIG, 0);
		regmap_write(i2s->regmap, XTFPGA_I2S_INT_MASK, 0);
		regmap_write(i2s->regmap, XTFPGA_I2S_INT_STATUS,
			     XTFPGA_I2S_INT_VALID);
	}
	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		xtfpga_i2s_runtime_suspend(&pdev->dev);
	return 0;
}