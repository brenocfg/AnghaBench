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
 int /*<<< orphan*/  btc8192e2ant_rf_shrink (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void btc8192e2ant_sw_mechanism1(struct btc_coexist *btcoexist,
				       bool shrink_rx_lpf, bool low_penalty_ra,
				       bool limited_dig, bool btlan_constrain)
{
	btc8192e2ant_rf_shrink(btcoexist, NORMAL_EXEC, shrink_rx_lpf);
}