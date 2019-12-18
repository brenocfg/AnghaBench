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
struct wcd9335_codec {int /*<<< orphan*/  sido_voltage; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIDO_VOLTAGE_NOMINAL_MV ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int wcd9335_cdc_req_mclk_enable (struct wcd9335_codec*,int) ; 
 int /*<<< orphan*/  wcd9335_codec_apply_sido_voltage (struct wcd9335_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcd9335_codec_update_sido_voltage (struct wcd9335_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _wcd9335_codec_enable_mclk(struct snd_soc_component *component,
				      int enable)
{
	struct wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	int ret;

	if (enable) {
		ret = wcd9335_cdc_req_mclk_enable(wcd, true);
		if (ret)
			return ret;

		wcd9335_codec_apply_sido_voltage(wcd,
				SIDO_VOLTAGE_NOMINAL_MV);
	} else {
		wcd9335_codec_update_sido_voltage(wcd,
					wcd->sido_voltage);
		wcd9335_cdc_req_mclk_enable(wcd, false);
	}

	return 0;
}