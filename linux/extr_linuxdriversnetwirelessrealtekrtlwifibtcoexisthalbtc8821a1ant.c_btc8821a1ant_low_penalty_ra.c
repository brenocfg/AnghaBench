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
struct btc_coexist {int dummy; } ;
struct TYPE_2__ {int cur_low_penalty_ra; int pre_low_penalty_ra; } ;

/* Variables and functions */
 int /*<<< orphan*/  btc8821a1ant_set_sw_penalty_tx_rate (struct btc_coexist*,int) ; 
 TYPE_1__* coex_dm ; 

__attribute__((used)) static void btc8821a1ant_low_penalty_ra(struct btc_coexist *btcoexist,
					bool force_exec, bool low_penalty_ra)
{
	coex_dm->cur_low_penalty_ra = low_penalty_ra;

	if (!force_exec) {
		if (coex_dm->pre_low_penalty_ra == coex_dm->cur_low_penalty_ra)
			return;
	}
	btc8821a1ant_set_sw_penalty_tx_rate(btcoexist,
					    coex_dm->cur_low_penalty_ra);

	coex_dm->pre_low_penalty_ra = coex_dm->cur_low_penalty_ra;
}