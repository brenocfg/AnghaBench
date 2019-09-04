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
struct pfuze_chip {unsigned int chip_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int PFUZE100 ; 
 int /*<<< orphan*/  PFUZE100_DEVICEID ; 
 int /*<<< orphan*/  PFUZE100_FABID ; 
 int /*<<< orphan*/  PFUZE100_REVID ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int pfuze_identify(struct pfuze_chip *pfuze_chip)
{
	unsigned int value;
	int ret;

	ret = regmap_read(pfuze_chip->regmap, PFUZE100_DEVICEID, &value);
	if (ret)
		return ret;

	if (((value & 0x0f) == 0x8) && (pfuze_chip->chip_id == PFUZE100)) {
		/*
		 * Freescale misprogrammed 1-3% of parts prior to week 8 of 2013
		 * as ID=8 in PFUZE100
		 */
		dev_info(pfuze_chip->dev, "Assuming misprogrammed ID=0x8");
	} else if ((value & 0x0f) != pfuze_chip->chip_id &&
		   (value & 0xf0) >> 4 != pfuze_chip->chip_id &&
		   (value != pfuze_chip->chip_id)) {
		/* device id NOT match with your setting */
		dev_warn(pfuze_chip->dev, "Illegal ID: %x\n", value);
		return -ENODEV;
	}

	ret = regmap_read(pfuze_chip->regmap, PFUZE100_REVID, &value);
	if (ret)
		return ret;
	dev_info(pfuze_chip->dev,
		 "Full layer: %x, Metal layer: %x\n",
		 (value & 0xf0) >> 4, value & 0x0f);

	ret = regmap_read(pfuze_chip->regmap, PFUZE100_FABID, &value);
	if (ret)
		return ret;
	dev_info(pfuze_chip->dev, "FAB: %x, FIN: %x\n",
		 (value & 0xc) >> 2, value & 0x3);

	return 0;
}