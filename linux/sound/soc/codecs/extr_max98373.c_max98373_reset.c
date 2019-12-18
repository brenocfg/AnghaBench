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
struct max98373_priv {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX98373_R2000_SW_RESET ; 
 int /*<<< orphan*/  MAX98373_R21FF_REV_ID ; 
 int /*<<< orphan*/  MAX98373_SOFT_RESET ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void max98373_reset(struct max98373_priv *max98373, struct device *dev)
{
	int ret, reg, count;

	/* Software Reset */
	ret = regmap_update_bits(max98373->regmap,
		MAX98373_R2000_SW_RESET,
		MAX98373_SOFT_RESET,
		MAX98373_SOFT_RESET);
	if (ret)
		dev_err(dev, "Reset command failed. (ret:%d)\n", ret);

	count = 0;
	while (count < 3) {
		usleep_range(10000, 11000);
		/* Software Reset Verification */
		ret = regmap_read(max98373->regmap,
			MAX98373_R21FF_REV_ID, &reg);
		if (!ret) {
			dev_info(dev, "Reset completed (retry:%d)\n", count);
			return;
		}
		count++;
	}
	dev_err(dev, "Reset failed. (ret:%d)\n", ret);
}