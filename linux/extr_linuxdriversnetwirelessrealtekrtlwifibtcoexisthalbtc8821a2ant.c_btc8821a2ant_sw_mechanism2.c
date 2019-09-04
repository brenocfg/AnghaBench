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
typedef  int /*<<< orphan*/  u32 ;
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  btc8821a2ant_dac_swing (struct btc_coexist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc8821a2ant_sw_mechanism2(struct btc_coexist *btcoexist,
				       bool agc_table_shift, bool adc_back_off,
				       bool sw_dac_swing, u32 dac_swing_lvl)
{
	btc8821a2ant_dac_swing(btcoexist, NORMAL_EXEC, sw_dac_swing,
			       dac_swing_lvl);
}