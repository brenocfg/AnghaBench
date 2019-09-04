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
struct btc_coexist {int stop_coex_dm; } ;

/* Variables and functions */
 int /*<<< orphan*/  halbtc8723b1ant_init_hw_config (struct btc_coexist*,int,int) ; 

void ex_btc8723b1ant_init_hwconfig(struct btc_coexist *btcoexist,
				   bool wifi_only)
{
	halbtc8723b1ant_init_hw_config(btcoexist, true, wifi_only);
	btcoexist->stop_coex_dm = false;
}