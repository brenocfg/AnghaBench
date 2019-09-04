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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct btc_coexist {int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int*) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U1_LPS_MODE ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int,int*) ; 

__attribute__((used)) static void halbtc8822b2ant_ps_tdma_check_for_power_save_state(
	struct btc_coexist *btcoexist, bool new_ps_state)
{
	u8 lps_mode = 0x0;
	u8 h2c_parameter[5] = {0, 0, 0, 0x40, 0};
	u32 RTL97F_8822B = 0;

	if (RTL97F_8822B)
		return;

	btcoexist->btc_get(btcoexist, BTC_GET_U1_LPS_MODE, &lps_mode);

	if (lps_mode) { /* already under LPS state */
		if (new_ps_state) {
			/* keep state under LPS, do nothing. */
		} else {
			/* will leave LPS state, turn off psTdma first */
			btcoexist->btc_fill_h2c(btcoexist, 0x60, 5,
						h2c_parameter);
		}
	} else { /* NO PS state */
		if (new_ps_state) {
			/* will enter LPS state, turn off psTdma first */
			btcoexist->btc_fill_h2c(btcoexist, 0x60, 5,
						h2c_parameter);
		} else {
			/* keep state under NO PS state, do nothing. */
		}
	}
}