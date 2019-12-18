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
struct wcd9335_codec {int /*<<< orphan*/  dev; } ;
typedef  enum wcd9335_sido_voltage { ____Placeholder_wcd9335_sido_voltage } wcd9335_sido_voltage ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int wcd9335_cdc_req_mclk_enable (struct wcd9335_codec*,int) ; 
 int /*<<< orphan*/  wcd9335_codec_apply_sido_voltage (struct wcd9335_codec*,int) ; 

__attribute__((used)) static int wcd9335_codec_update_sido_voltage(struct wcd9335_codec *wcd,
					     enum wcd9335_sido_voltage req_mv)
{
	int ret = 0;

	/* enable mclk before setting SIDO voltage */
	ret = wcd9335_cdc_req_mclk_enable(wcd, true);
	if (ret) {
		dev_err(wcd->dev, "Ext clk enable failed\n");
		goto err;
	}

	wcd9335_codec_apply_sido_voltage(wcd, req_mv);
	wcd9335_cdc_req_mclk_enable(wcd, false);

err:
	return ret;
}