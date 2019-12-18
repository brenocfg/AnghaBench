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
typedef  enum adau17x1_type { ____Placeholder_adau17x1_type } adau17x1_type ;

/* Variables and functions */
#define  ADAU1381 129 
 char* ADAU1381_FIRMWARE ; 
#define  ADAU1781 128 
 char* ADAU1781_FIRMWARE ; 
 int EINVAL ; 
 int /*<<< orphan*/  adau1781_component_driver ; 
 int /*<<< orphan*/  adau1781_dai_driver ; 
 int adau17x1_probe (struct device*,struct regmap*,int,void (*) (struct device*),char const*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int adau1781_probe(struct device *dev, struct regmap *regmap,
	enum adau17x1_type type, void (*switch_mode)(struct device *dev))
{
	const char *firmware_name;
	int ret;

	switch (type) {
	case ADAU1381:
		firmware_name = ADAU1381_FIRMWARE;
		break;
	case ADAU1781:
		firmware_name = ADAU1781_FIRMWARE;
		break;
	default:
		return -EINVAL;
	}

	ret = adau17x1_probe(dev, regmap, type, switch_mode, firmware_name);
	if (ret)
		return ret;

	return devm_snd_soc_register_component(dev, &adau1781_component_driver,
		&adau1781_dai_driver, 1);
}