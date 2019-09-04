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
struct device {int dummy; } ;
typedef  enum da7219_micbias_voltage { ____Placeholder_da7219_micbias_voltage } da7219_micbias_voltage ;

/* Variables and functions */
 int DA7219_MICBIAS_1_6V ; 
 int DA7219_MICBIAS_1_8V ; 
 int DA7219_MICBIAS_2_0V ; 
 int DA7219_MICBIAS_2_2V ; 
 int DA7219_MICBIAS_2_4V ; 
 int DA7219_MICBIAS_2_6V ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 

__attribute__((used)) static enum da7219_micbias_voltage
	da7219_fw_micbias_lvl(struct device *dev, u32 val)
{
	switch (val) {
	case 1600:
		return DA7219_MICBIAS_1_6V;
	case 1800:
		return DA7219_MICBIAS_1_8V;
	case 2000:
		return DA7219_MICBIAS_2_0V;
	case 2200:
		return DA7219_MICBIAS_2_2V;
	case 2400:
		return DA7219_MICBIAS_2_4V;
	case 2600:
		return DA7219_MICBIAS_2_6V;
	default:
		dev_warn(dev, "Invalid micbias level");
		return DA7219_MICBIAS_2_2V;
	}
}