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
struct lp8788_charger_platform_data {int /*<<< orphan*/  adc_batt_temp; int /*<<< orphan*/  adc_vbatt; } ;
struct lp8788_charger {struct iio_channel** chan; struct lp8788_charger_platform_data* pdata; } ;
struct iio_channel {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct iio_channel*) ; 
 size_t LP8788_BATT_TEMP ; 
 size_t LP8788_VBATT ; 
 struct iio_channel* iio_channel_get (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lp8788_setup_adc_channel(struct device *dev,
				struct lp8788_charger *pchg)
{
	struct lp8788_charger_platform_data *pdata = pchg->pdata;
	struct iio_channel *chan;

	if (!pdata)
		return;

	/* ADC channel for battery voltage */
	chan = iio_channel_get(dev, pdata->adc_vbatt);
	pchg->chan[LP8788_VBATT] = IS_ERR(chan) ? NULL : chan;

	/* ADC channel for battery temperature */
	chan = iio_channel_get(dev, pdata->adc_batt_temp);
	pchg->chan[LP8788_BATT_TEMP] = IS_ERR(chan) ? NULL : chan;
}