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
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  btc8821a1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8821a1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void btc8821a1ant_act_bt_sco_hid_only_busy(struct btc_coexist *btcoexist,
						  u8 wifi_status)
{
	/* tdma and coex table */
	btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 5);

	btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
}