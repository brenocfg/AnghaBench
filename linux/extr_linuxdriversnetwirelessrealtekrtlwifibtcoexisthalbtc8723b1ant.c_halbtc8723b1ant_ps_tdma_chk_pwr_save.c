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
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U1_LPS_MODE ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b1ant_ps_tdma_chk_pwr_save(struct btc_coexist *btcoexist,
					  bool new_ps_state)
{
	u8 lps_mode = 0x0;

	btcoexist->btc_get(btcoexist, BTC_GET_U1_LPS_MODE, &lps_mode);

	if (lps_mode) {
		/* already under LPS state */
		if (new_ps_state) {
			/* keep state under LPS, do nothing. */
		} else {
			/* will leave LPS state, turn off psTdma first */
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						false, 0);
		}
	} else {
		/* NO PS state */
		if (new_ps_state) {
			/* will enter LPS state, turn off psTdma first */
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						false, 0);
		} else {
			/* keep state under NO PS state, do nothing. */
		}
	}
}