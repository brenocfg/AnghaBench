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
struct rtl_priv {int dummy; } ;
struct btc_coexist {int (* btc_read_1byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  dbg_mode_2ant; struct rtl_priv* adapter; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub11 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub12 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub13 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub14 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub15 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub16 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub17 (struct btc_coexist*,int,int,int) ; 
 int stub2 (struct btc_coexist*,int) ; 
 int stub3 (struct btc_coexist*,int) ; 
 int stub4 (struct btc_coexist*,int) ; 
 int stub5 (struct btc_coexist*,int) ; 
 int stub6 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void halbtc8822b2ant_enable_gnt_to_gpio(struct btc_coexist *btcoexist,
					       bool isenable)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u8 bit_val[5] = {0, 0, 0, 0, 0};

	if (!btcoexist->dbg_mode_2ant)
		return;

	if (isenable) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], enable_gnt_to_gpio!!\n");

		/* enable GNT_WL, GNT_BT to GPIO for debug */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x73, 0x8, 0x1);

		/* store original value */
		bit_val[0] =
			(btcoexist->btc_read_1byte(btcoexist, 0x66) & BIT(4)) >>
			4; /*0x66[4] */
		bit_val[1] = (btcoexist->btc_read_1byte(btcoexist, 0x67) &
			      BIT(0)); /*0x66[8] */
		bit_val[2] =
			(btcoexist->btc_read_1byte(btcoexist, 0x42) & BIT(3)) >>
			3; /*0x40[19] */
		bit_val[3] =
			(btcoexist->btc_read_1byte(btcoexist, 0x65) & BIT(7)) >>
			7; /*0x64[15] */
		bit_val[4] =
			(btcoexist->btc_read_1byte(btcoexist, 0x72) & BIT(2)) >>
			2; /*0x70[18] */

		/*  switch GPIO Mux */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x66, BIT(4),
						   0x0); /*0x66[4] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x67, BIT(0),
						   0x0); /*0x66[8] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x42, BIT(3),
						   0x0); /*0x40[19] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x65, BIT(7),
						   0x0); /*0x64[15] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x72, BIT(2),
						   0x0); /*0x70[18] = 0 */

	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], disable_gnt_to_gpio!!\n");

		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x73, 0x8, 0x0);

		/*  Restore original value  */
		/*  switch GPIO Mux */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x66, BIT(4),
						   bit_val[0]); /*0x66[4] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x67, BIT(0),
						   bit_val[1]); /*0x66[8] = 0 */
		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x42, BIT(3), bit_val[2]); /*0x40[19] = 0 */
		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x65, BIT(7), bit_val[3]); /*0x64[15] = 0 */
		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x72, BIT(2), bit_val[4]); /*0x70[18] = 0 */
	}
}