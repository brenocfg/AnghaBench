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
struct btc_coexist {int /*<<< orphan*/  (* btc_phydm_modify_ra_pcr_threshold ) (struct btc_coexist*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_2__ {int cur_low_penalty_ra; int pre_low_penalty_ra; } ;

/* Variables and functions */
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void halbtc8822b2ant_low_penalty_ra(struct btc_coexist *btcoexist,
					   bool force_exec, bool low_penalty_ra)
{
	coex_dm->cur_low_penalty_ra = low_penalty_ra;

	if (!force_exec) {
		if (coex_dm->pre_low_penalty_ra == coex_dm->cur_low_penalty_ra)
			return;
	}

	if (low_penalty_ra)
		btcoexist->btc_phydm_modify_ra_pcr_threshold(btcoexist, 0, 50);
	else
		btcoexist->btc_phydm_modify_ra_pcr_threshold(btcoexist, 0, 0);

	coex_dm->pre_low_penalty_ra = coex_dm->cur_low_penalty_ra;
}