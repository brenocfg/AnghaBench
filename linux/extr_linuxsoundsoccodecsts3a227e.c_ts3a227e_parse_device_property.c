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
typedef  int u32 ;
struct ts3a227e {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICBIAS_SETTING_MASK ; 
 int MICBIAS_SETTING_SFT ; 
 int /*<<< orphan*/  TS3A227E_REG_SETTING_3 ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ts3a227e_parse_device_property(struct ts3a227e *ts3a227e,
				struct device *dev)
{
	u32 micbias;
	int err;

	err = device_property_read_u32(dev, "ti,micbias", &micbias);
	if (!err) {
		regmap_update_bits(ts3a227e->regmap, TS3A227E_REG_SETTING_3,
			MICBIAS_SETTING_MASK,
			(micbias & 0x07) << MICBIAS_SETTING_SFT);
	}

	return 0;
}