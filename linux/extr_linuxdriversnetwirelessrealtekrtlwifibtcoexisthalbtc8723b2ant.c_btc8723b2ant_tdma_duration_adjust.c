#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
typedef  int s32 ;
struct TYPE_4__ {int auto_tdma_adjust; int ps_tdma_du_adj_type; int cur_ps_tdma; } ;
struct TYPE_3__ {int bt_retry_cnt; int low_priority_tx; int low_priority_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  btc8723b2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void btc8723b2ant_tdma_duration_adjust(struct btc_coexist *btcoexist,
					  bool sco_hid, bool tx_pause,
					  u8 max_interval)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static s32 up, dn, m, n, wait_count;
	/*0: no change, +1: increase WiFi duration, -1: decrease WiFi duration*/
	s32 result;
	u8 retry_count = 0;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], TdmaDurationAdjust()\n");

	if (!coex_dm->auto_tdma_adjust) {
		coex_dm->auto_tdma_adjust = true;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], first run TdmaDurationAdjust()!!\n");
		if (sco_hid) {
			if (tx_pause) {
				if (max_interval == 1) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 13);
					coex_dm->ps_tdma_du_adj_type = 13;
				} else if (max_interval == 2) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				} else if (max_interval == 3) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				} else {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				}
			} else {
				if (max_interval == 1) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 9);
					coex_dm->ps_tdma_du_adj_type = 9;
				} else if (max_interval == 2) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				} else if (max_interval == 3) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
						     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				} else {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				}
			}
		} else {
			if (tx_pause) {
				if (max_interval == 1) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 5);
					coex_dm->ps_tdma_du_adj_type = 5;
				} else if (max_interval == 2) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				} else if (max_interval == 3) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				} else {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				}
			} else {
				if (max_interval == 1) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 1);
					coex_dm->ps_tdma_du_adj_type = 1;
				} else if (max_interval == 2) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				} else if (max_interval == 3) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				} else {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				}
			}
		}

		up = 0;
		dn = 0;
		m = 1;
		n = 3;
		result = 0;
		wait_count = 0;
	} else {
		/*accquire the BT TRx retry count from BT_Info byte2*/
		retry_count = coex_sta->bt_retry_cnt;

		if ((coex_sta->low_priority_tx) > 1050 ||
		    (coex_sta->low_priority_rx) > 1250)
			retry_count++;

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], retry_count = %d\n", retry_count);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], up=%d, dn=%d, m=%d, n=%d, wait_count=%d\n",
			 up, dn, m, n, wait_count);
		result = 0;
		wait_count++;
		 /* no retry in the last 2-second duration*/
		if (retry_count == 0) {
			up++;
			dn--;

			if (dn <= 0)
				dn = 0;

			if (up >= n) {
				/* if retry count during continuous n*2
				 * seconds is 0, enlarge WiFi duration
				 */
				wait_count = 0;
				n = 3;
				up = 0;
				dn = 0;
				result = 1;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], Increase wifi duration!!\n");
			} /* <=3 retry in the last 2-second duration*/
		} else if (retry_count <= 3) {
			up--;
			dn++;

			if (up <= 0)
				up = 0;

			if (dn == 2) {
				/* if continuous 2 retry count(every 2
				 * seconds) >0 and < 3, reduce WiFi duration
				 */
				if (wait_count <= 2)
					/* avoid loop between the two levels */
					m++;
				else
					m = 1;

				if (m >= 20)
					/* maximum of m = 20 ' will recheck if
					 * need to adjust wifi duration in
					 * maximum time interval 120 seconds
					 */
					m = 20;

				n = 3 * m;
				up = 0;
				dn = 0;
				wait_count = 0;
				result = -1;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], Decrease wifi duration for retry_counter<3!!\n");
			}
		} else {
			/* retry count > 3, once retry count > 3, to reduce
			 *  WiFi duration
			 */
			if (wait_count == 1)
				/* to avoid loop between the two levels */
				m++;
			else
				m = 1;

			if (m >= 20)
				/* maximum of m = 20 ' will recheck if need to
				 * adjust wifi duration in maximum time interval
				 * 120 seconds
				 */
				m = 20;

			n = 3 * m;
			up = 0;
			dn = 0;
			wait_count = 0;
			result = -1;
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Decrease wifi duration for retry_counter>3!!\n");
		}

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], max Interval = %d\n", max_interval);
		if (max_interval == 1) {
			if (tx_pause) {
				if (coex_dm->cur_ps_tdma == 71) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 5);
					coex_dm->ps_tdma_du_adj_type = 5;
				} else if (coex_dm->cur_ps_tdma == 1) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 5);
					coex_dm->ps_tdma_du_adj_type = 5;
				} else if (coex_dm->cur_ps_tdma == 2) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				} else if (coex_dm->cur_ps_tdma == 3) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				} else if (coex_dm->cur_ps_tdma == 4) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 8);
					coex_dm->ps_tdma_du_adj_type = 8;
				}
				if (coex_dm->cur_ps_tdma == 9) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 13);
					coex_dm->ps_tdma_du_adj_type = 13;
				} else if (coex_dm->cur_ps_tdma == 10) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				} else if (coex_dm->cur_ps_tdma == 11) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				} else if (coex_dm->cur_ps_tdma == 12) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 16);
					coex_dm->ps_tdma_du_adj_type = 16;
				}

				if (result == -1) {
					if (coex_dm->cur_ps_tdma == 5) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					} else if (coex_dm->cur_ps_tdma == 6) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					} else if (coex_dm->cur_ps_tdma == 7) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 8);
						coex_dm->ps_tdma_du_adj_type =
							8;
					} else if (coex_dm->cur_ps_tdma == 13) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					} else if (coex_dm->cur_ps_tdma == 14) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					} else if (coex_dm->cur_ps_tdma == 15) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 16);
						coex_dm->ps_tdma_du_adj_type =
							16;
					}
				} else if (result == 1) {
					if (coex_dm->cur_ps_tdma == 8) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					} else if (coex_dm->cur_ps_tdma == 7) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					} else if (coex_dm->cur_ps_tdma == 6) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 5);
						coex_dm->ps_tdma_du_adj_type =
							5;
					} else if (coex_dm->cur_ps_tdma == 16) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					} else if (coex_dm->cur_ps_tdma == 15) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					} else if (coex_dm->cur_ps_tdma == 14) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 13);
						coex_dm->ps_tdma_du_adj_type =
							13;
					}
				}
			} else {
				if (coex_dm->cur_ps_tdma == 5) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 71);
					coex_dm->ps_tdma_du_adj_type = 71;
				} else if (coex_dm->cur_ps_tdma == 6) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				} else if (coex_dm->cur_ps_tdma == 7) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				} else if (coex_dm->cur_ps_tdma == 8) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 4);
					coex_dm->ps_tdma_du_adj_type = 4;
				}
				if (coex_dm->cur_ps_tdma == 13) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 9);
					coex_dm->ps_tdma_du_adj_type = 9;
				} else if (coex_dm->cur_ps_tdma == 14) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				} else if (coex_dm->cur_ps_tdma == 15) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				} else if (coex_dm->cur_ps_tdma == 16) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 12);
					coex_dm->ps_tdma_du_adj_type = 12;
				}

				if (result == -1) {
					if (coex_dm->cur_ps_tdma == 71) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 1);
						coex_dm->ps_tdma_du_adj_type =
							1;
					} else if (coex_dm->cur_ps_tdma == 1) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					} else if (coex_dm->cur_ps_tdma == 2) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					} else if (coex_dm->cur_ps_tdma == 3) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 4);
						coex_dm->ps_tdma_du_adj_type =
							4;
					} else if (coex_dm->cur_ps_tdma == 9) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					} else if (coex_dm->cur_ps_tdma == 10) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					} else if (coex_dm->cur_ps_tdma == 11) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 12);
						coex_dm->ps_tdma_du_adj_type =
							12;
					}
				} else if (result == 1) {
					if (coex_dm->cur_ps_tdma == 4) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					} else if (coex_dm->cur_ps_tdma == 3) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					} else if (coex_dm->cur_ps_tdma == 2) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 1);
						coex_dm->ps_tdma_du_adj_type =
							1;
					} else if (coex_dm->cur_ps_tdma == 1) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 71);
						coex_dm->ps_tdma_du_adj_type =
							71;
					} else if (coex_dm->cur_ps_tdma == 12) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					} else if (coex_dm->cur_ps_tdma == 11) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					} else if (coex_dm->cur_ps_tdma == 10) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 9);
						coex_dm->ps_tdma_du_adj_type =
							9;
					}
				}
			}
		} else if (max_interval == 2) {
			if (tx_pause) {
				if (coex_dm->cur_ps_tdma == 1) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				} else if (coex_dm->cur_ps_tdma == 2) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				} else if (coex_dm->cur_ps_tdma == 3) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				} else if (coex_dm->cur_ps_tdma == 4) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 8);
					coex_dm->ps_tdma_du_adj_type = 8;
				}
				if (coex_dm->cur_ps_tdma == 9) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				} else if (coex_dm->cur_ps_tdma == 10) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				} else if (coex_dm->cur_ps_tdma == 11) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				} else if (coex_dm->cur_ps_tdma == 12) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 16);
					coex_dm->ps_tdma_du_adj_type = 16;
				}
				if (result == -1) {
					if (coex_dm->cur_ps_tdma == 5) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					} else if (coex_dm->cur_ps_tdma == 6) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					} else if (coex_dm->cur_ps_tdma == 7) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 8);
						coex_dm->ps_tdma_du_adj_type =
							8;
					} else if (coex_dm->cur_ps_tdma == 13) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					} else if (coex_dm->cur_ps_tdma == 14) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					} else if (coex_dm->cur_ps_tdma == 15) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 16);
						coex_dm->ps_tdma_du_adj_type =
							16;
					}
				} else if (result == 1) {
					if (coex_dm->cur_ps_tdma == 8) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					} else if (coex_dm->cur_ps_tdma == 7) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					} else if (coex_dm->cur_ps_tdma == 6) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					} else if (coex_dm->cur_ps_tdma == 16) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					} else if (coex_dm->cur_ps_tdma == 15) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					} else if (coex_dm->cur_ps_tdma == 14) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					}
				}
			} else {
				if (coex_dm->cur_ps_tdma == 5) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				} else if (coex_dm->cur_ps_tdma == 6) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				} else if (coex_dm->cur_ps_tdma == 7) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				} else if (coex_dm->cur_ps_tdma == 8) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 4);
					coex_dm->ps_tdma_du_adj_type = 4;
				}
				if (coex_dm->cur_ps_tdma == 13) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				} else if (coex_dm->cur_ps_tdma == 14) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				} else if (coex_dm->cur_ps_tdma == 15) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				} else if (coex_dm->cur_ps_tdma == 16) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 12);
					coex_dm->ps_tdma_du_adj_type = 12;
				}
				if (result == -1) {
					if (coex_dm->cur_ps_tdma == 1) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					} else if (coex_dm->cur_ps_tdma == 2) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					} else if (coex_dm->cur_ps_tdma == 3) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 4);
						coex_dm->ps_tdma_du_adj_type =
							4;
					} else if (coex_dm->cur_ps_tdma == 9) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					} else if (coex_dm->cur_ps_tdma == 10) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					} else if (coex_dm->cur_ps_tdma == 11) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 12);
						coex_dm->ps_tdma_du_adj_type =
							12;
					}
				} else if (result == 1) {
					if (coex_dm->cur_ps_tdma == 4) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					} else if (coex_dm->cur_ps_tdma == 3) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					} else if (coex_dm->cur_ps_tdma == 2) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					} else if (coex_dm->cur_ps_tdma == 12) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					} else if (coex_dm->cur_ps_tdma == 11) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					} else if (coex_dm->cur_ps_tdma == 10) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					}
				}
			}
		} else if (max_interval == 3) {
			if (tx_pause) {
				if (coex_dm->cur_ps_tdma == 1) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				} else if (coex_dm->cur_ps_tdma == 2) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				} else if (coex_dm->cur_ps_tdma == 3) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				} else if (coex_dm->cur_ps_tdma == 4) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 8);
					coex_dm->ps_tdma_du_adj_type = 8;
				}
				if (coex_dm->cur_ps_tdma == 9) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				} else if (coex_dm->cur_ps_tdma == 10) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				} else if (coex_dm->cur_ps_tdma == 11) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				} else if (coex_dm->cur_ps_tdma == 12) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 16);
					coex_dm->ps_tdma_du_adj_type = 16;
				}
				if (result == -1) {
					if (coex_dm->cur_ps_tdma == 5) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					} else if (coex_dm->cur_ps_tdma == 6) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					} else if (coex_dm->cur_ps_tdma == 7) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 8);
						coex_dm->ps_tdma_du_adj_type =
							8;
					} else if (coex_dm->cur_ps_tdma == 13) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					} else if (coex_dm->cur_ps_tdma == 14) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					} else if (coex_dm->cur_ps_tdma == 15) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 16);
						coex_dm->ps_tdma_du_adj_type =
							16;
					}
				} else if (result == 1) {
					if (coex_dm->cur_ps_tdma == 8) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					} else if (coex_dm->cur_ps_tdma == 7) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					} else if (coex_dm->cur_ps_tdma == 6) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					} else if (coex_dm->cur_ps_tdma == 16) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					} else if (coex_dm->cur_ps_tdma == 15) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					} else if (coex_dm->cur_ps_tdma == 14) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					}
				}
			} else {
				if (coex_dm->cur_ps_tdma == 5) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				} else if (coex_dm->cur_ps_tdma == 6) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				} else if (coex_dm->cur_ps_tdma == 7) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				} else if (coex_dm->cur_ps_tdma == 8) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 4);
					coex_dm->ps_tdma_du_adj_type = 4;
				}
				if (coex_dm->cur_ps_tdma == 13) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				} else if (coex_dm->cur_ps_tdma == 14) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				} else if (coex_dm->cur_ps_tdma == 15) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				} else if (coex_dm->cur_ps_tdma == 16) {
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 12);
					coex_dm->ps_tdma_du_adj_type = 12;
				}
				if (result == -1) {
					if (coex_dm->cur_ps_tdma == 1) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					} else if (coex_dm->cur_ps_tdma == 2) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					} else if (coex_dm->cur_ps_tdma == 3) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 4);
						coex_dm->ps_tdma_du_adj_type =
							4;
					} else if (coex_dm->cur_ps_tdma == 9) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					} else if (coex_dm->cur_ps_tdma == 10) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					} else if (coex_dm->cur_ps_tdma == 11) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 12);
						coex_dm->ps_tdma_du_adj_type =
							12;
					}
				} else if (result == 1) {
					if (coex_dm->cur_ps_tdma == 4) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					} else if (coex_dm->cur_ps_tdma == 3) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					} else if (coex_dm->cur_ps_tdma == 2) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					} else if (coex_dm->cur_ps_tdma == 12) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					} else if (coex_dm->cur_ps_tdma == 11) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					} else if (coex_dm->cur_ps_tdma == 10) {
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					}
				}
			}
		}
	}

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], max Interval = %d\n", max_interval);

	/* if current PsTdma not match with the recorded one (scan, dhcp, ...),
	 * then we have to adjust it back to the previous recorded one.
	 */
	if (coex_dm->cur_ps_tdma != coex_dm->ps_tdma_du_adj_type) {
		bool scan = false, link = false, roam = false;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], PsTdma type mismatch!!!, curPsTdma=%d, recordPsTdma=%d\n",
			 coex_dm->cur_ps_tdma, coex_dm->ps_tdma_du_adj_type);

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

		if (!scan && !link && !roam)
			btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
					     coex_dm->ps_tdma_du_adj_type);
		else
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], roaming/link/scan is under progress, will adjust next time!!!\n");
	}
}