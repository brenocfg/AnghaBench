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
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int CPCAP_BIT_AUDIO_LOW_PWR ; 
 int CPCAP_BIT_AUDIO_NORMAL_MODE ; 
 int EINVAL ; 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int cpcap_regulator_set_mode(struct regulator_dev *rdev,
				    unsigned int mode)
{
	int value;

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		value = CPCAP_BIT_AUDIO_NORMAL_MODE;
		break;
	case REGULATOR_MODE_STANDBY:
		value = CPCAP_BIT_AUDIO_LOW_PWR;
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  CPCAP_BIT_AUDIO_LOW_PWR, value);
}