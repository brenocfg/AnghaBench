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
union power_supply_propval {int intval; } ;
typedef  int u8 ;
struct power_supply {int dummy; } ;
struct pcf50633_mbc {int /*<<< orphan*/  usb_online; int /*<<< orphan*/  pcf; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int PCF50633_MBCC7_USB_500mA ; 
 int PCF50633_MBCC7_USB_MASK ; 
 int /*<<< orphan*/  PCF50633_REG_MBCC7 ; 
#define  POWER_SUPPLY_PROP_ONLINE 128 
 int pcf50633_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcf50633_mbc* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int usb_get_property(struct power_supply *psy,
			enum power_supply_property psp,
			union power_supply_propval *val)
{
	struct pcf50633_mbc *mbc = power_supply_get_drvdata(psy);
	int ret = 0;
	u8 usblim = pcf50633_reg_read(mbc->pcf, PCF50633_REG_MBCC7) &
						PCF50633_MBCC7_USB_MASK;

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = mbc->usb_online &&
				(usblim <= PCF50633_MBCC7_USB_500mA);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}