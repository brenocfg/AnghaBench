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
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct cs42l51_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS42L51_CHIP_ID ; 
 int /*<<< orphan*/  CS42L51_CHIP_REV_A ; 
 int /*<<< orphan*/  CS42L51_CHIP_REV_B ; 
 int /*<<< orphan*/  CS42L51_CHIP_REV_ID ; 
 unsigned int CS42L51_CHIP_REV_MASK ; 
 unsigned int CS42L51_MK_CHIP_REV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  cs42l51_dai ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct cs42l51_private*) ; 
 struct cs42l51_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  soc_component_device_cs42l51 ; 

int cs42l51_probe(struct device *dev, struct regmap *regmap)
{
	struct cs42l51_private *cs42l51;
	unsigned int val;
	int ret;

	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	cs42l51 = devm_kzalloc(dev, sizeof(struct cs42l51_private),
			       GFP_KERNEL);
	if (!cs42l51)
		return -ENOMEM;

	dev_set_drvdata(dev, cs42l51);

	/* Verify that we have a CS42L51 */
	ret = regmap_read(regmap, CS42L51_CHIP_REV_ID, &val);
	if (ret < 0) {
		dev_err(dev, "failed to read I2C\n");
		goto error;
	}

	if ((val != CS42L51_MK_CHIP_REV(CS42L51_CHIP_ID, CS42L51_CHIP_REV_A)) &&
	    (val != CS42L51_MK_CHIP_REV(CS42L51_CHIP_ID, CS42L51_CHIP_REV_B))) {
		dev_err(dev, "Invalid chip id: %x\n", val);
		ret = -ENODEV;
		goto error;
	}
	dev_info(dev, "Cirrus Logic CS42L51, Revision: %02X\n",
		 val & CS42L51_CHIP_REV_MASK);

	ret = devm_snd_soc_register_component(dev,
			&soc_component_device_cs42l51, &cs42l51_dai, 1);
error:
	return ret;
}