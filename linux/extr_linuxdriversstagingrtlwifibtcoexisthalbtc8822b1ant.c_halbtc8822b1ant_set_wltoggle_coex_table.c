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
struct btc_coexist {int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int,int*) ; 

__attribute__((used)) static void halbtc8822b1ant_set_wltoggle_coex_table(
	struct btc_coexist *btcoexist, bool force_exec, u8 interval,
	u8 val0x6c4_b0, u8 val0x6c4_b1, u8 val0x6c4_b2, u8 val0x6c4_b3)
{
	static u8 pre_h2c_parameter[6] = {0};
	u8 cur_h2c_parameter[6] = {0};
	u8 i, match_cnt = 0;

	cur_h2c_parameter[0] = 0x7; /* op_code, 0x7= wlan toggle slot*/

	cur_h2c_parameter[1] = interval;
	cur_h2c_parameter[2] = val0x6c4_b0;
	cur_h2c_parameter[3] = val0x6c4_b1;
	cur_h2c_parameter[4] = val0x6c4_b2;
	cur_h2c_parameter[5] = val0x6c4_b3;

	if (!force_exec) {
		for (i = 1; i <= 5; i++) {
			if (cur_h2c_parameter[i] != pre_h2c_parameter[i])
				break;

			match_cnt++;
		}

		if (match_cnt == 5)
			return;
	}

	for (i = 1; i <= 5; i++)
		pre_h2c_parameter[i] = cur_h2c_parameter[i];

	btcoexist->btc_fill_h2c(btcoexist, 0x69, 6, cur_h2c_parameter);
}