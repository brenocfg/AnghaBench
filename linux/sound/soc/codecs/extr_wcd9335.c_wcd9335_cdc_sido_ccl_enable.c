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
struct wcd9335_codec {int sido_ccl_cnt; int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCD9335_SIDO_SIDO_CCL_10 ; 
 int /*<<< orphan*/  WCD9335_SIDO_SIDO_CCL_10_ICHARG_PWR_SEL_C320FF ; 
 int /*<<< orphan*/  WCD9335_SIDO_SIDO_CCL_DEF_VALUE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wcd9335_cdc_sido_ccl_enable(struct wcd9335_codec *wcd,
					bool ccl_flag)
{
	struct snd_soc_component *comp = wcd->component;

	if (ccl_flag) {
		if (++wcd->sido_ccl_cnt == 1)
			snd_soc_component_write(comp, WCD9335_SIDO_SIDO_CCL_10,
					WCD9335_SIDO_SIDO_CCL_DEF_VALUE);
	} else {
		if (wcd->sido_ccl_cnt == 0) {
			dev_err(wcd->dev, "sido_ccl already disabled\n");
			return;
		}
		if (--wcd->sido_ccl_cnt == 0)
			snd_soc_component_write(comp, WCD9335_SIDO_SIDO_CCL_10,
				WCD9335_SIDO_SIDO_CCL_10_ICHARG_PWR_SEL_C320FF);
	}
}