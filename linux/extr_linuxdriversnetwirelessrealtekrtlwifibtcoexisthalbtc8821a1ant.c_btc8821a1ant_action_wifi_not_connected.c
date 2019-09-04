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
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  btc8821a1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a1ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8821a1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static
void btc8821a1ant_action_wifi_not_connected(struct btc_coexist *btcoexist)
{
	/* power save state */
	btc8821a1ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/* tdma and coex table */
	btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
	btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
}