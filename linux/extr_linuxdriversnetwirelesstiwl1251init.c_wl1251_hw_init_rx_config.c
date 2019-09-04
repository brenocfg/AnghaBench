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
typedef  int /*<<< orphan*/  u32 ;
struct wl1251 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_MSDU_LIFETIME_DEF ; 
 int wl1251_acx_rx_config (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1251_acx_rx_msdu_life_time (struct wl1251*,int /*<<< orphan*/ ) ; 

int wl1251_hw_init_rx_config(struct wl1251 *wl, u32 config, u32 filter)
{
	int ret;

	ret = wl1251_acx_rx_msdu_life_time(wl, RX_MSDU_LIFETIME_DEF);
	if (ret < 0)
		return ret;

	ret = wl1251_acx_rx_config(wl, config, filter);
	if (ret < 0)
		return ret;

	return 0;
}