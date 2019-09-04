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
struct btc_coexist {int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void halbtc8723b1ant_set_bt_auto_report(struct btc_coexist *btcoexist,
					       bool enable_auto_report)
{
	u8 h2c_parameter[1] = {0};

	h2c_parameter[0] = 0;

	if (enable_auto_report)
		h2c_parameter[0] |= BIT(0);

	btcoexist->btc_fill_h2c(btcoexist, 0x68, 1, h2c_parameter);
}