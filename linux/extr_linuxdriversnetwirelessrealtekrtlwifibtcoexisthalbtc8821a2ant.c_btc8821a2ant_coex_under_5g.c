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
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  btc8821a2ant_coex_all_off (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_ignore_wlan_act (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void btc8821a2ant_coex_under_5g(struct btc_coexist *btcoexist)
{
	btc8821a2ant_coex_all_off(btcoexist);
	btc8821a2ant_ignore_wlan_act(btcoexist, NORMAL_EXEC, true);
}