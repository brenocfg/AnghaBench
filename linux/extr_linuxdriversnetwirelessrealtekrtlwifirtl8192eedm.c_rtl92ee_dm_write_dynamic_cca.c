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
typedef  scalar_t__ u8 ;
struct ieee80211_hw {int dummy; } ;
struct dynamic_primary_cca {scalar_t__ mf_state; } ;
struct TYPE_2__ {struct dynamic_primary_cca primarycca; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DM_REG_L1SBD_PD_CH_11N ; 
 TYPE_1__* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void rtl92ee_dm_write_dynamic_cca(struct ieee80211_hw *hw,
					 u8 cur_mf_state)
{
	struct dynamic_primary_cca *primarycca = &rtl_priv(hw)->primarycca;

	if (primarycca->mf_state != cur_mf_state)
		rtl_set_bbreg(hw, DM_REG_L1SBD_PD_CH_11N, BIT(8) | BIT(7),
			      cur_mf_state);

	primarycca->mf_state = cur_mf_state;
}