#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  cnt_dbg_ctrl; } ;
struct btc_coexist {TYPE_1__ statistics; } ;

/* Variables and functions */
 int /*<<< orphan*/  halbtc_is_bt_coexist_available (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc_leave_low_power (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc_normal_low_power (struct btc_coexist*) ; 

void exhalbtc_dbg_control(struct btc_coexist *btcoexist,
			  u8 code, u8 len, u8 *data)
{
	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;
	btcoexist->statistics.cnt_dbg_ctrl++;

	halbtc_leave_low_power(btcoexist);

	halbtc_normal_low_power(btcoexist);
}