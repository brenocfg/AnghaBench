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
typedef  int /*<<< orphan*/  u8 ;
struct wifi_only_cfg {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8822B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_hal8822b_wifi_only_switchbandnotify (struct wifi_only_cfg*,int /*<<< orphan*/ ) ; 

void exhalbtc_switch_band_notify_wifi_only(struct wifi_only_cfg *wifionly_cfg,
					   u8 is_5g)
{
	if (IS_HARDWARE_TYPE_8822B(wifionly_cfg->adapter))
		ex_hal8822b_wifi_only_switchbandnotify(wifionly_cfg, is_5g);
}