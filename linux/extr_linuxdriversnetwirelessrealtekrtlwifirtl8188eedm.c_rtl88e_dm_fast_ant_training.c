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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  fast_antenna_training_timer; } ;
struct rtl_priv {TYPE_1__ works; } ;
struct fast_ant_training {scalar_t__ fat_state; int* ant_cnt; int* ant_ave; int* ant_sum; int* antsel_a; size_t train_idx; int* antsel_b; int* antsel_c; } ;
struct rtl_dm {struct fast_ant_training fat_table; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DM_REG_IGI_A_11N ; 
 int /*<<< orphan*/  DM_REG_RX_ANT_CTRL_11N ; 
 int /*<<< orphan*/  DM_REG_TXAGC_A_1_MCS32_11N ; 
 int /*<<< orphan*/  DM_REG_TX_ANT_CTRL_11N ; 
 scalar_t__ FAT_NORMAL_STATE ; 
 scalar_t__ FAT_TRAINING_STATE ; 
 scalar_t__ MSECS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_WATCH_DOG_TIME ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rtl88e_set_next_mac_address_target (struct ieee80211_hw*) ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl88e_dm_fast_ant_training(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	struct fast_ant_training *pfat_table = &rtldm->fat_table;
	u32 i, max_rssi = 0;
	u8 target_ant = 2;
	bool bpkt_filter_match = false;

	if (pfat_table->fat_state == FAT_TRAINING_STATE) {
		for (i = 0; i < 7; i++) {
			if (pfat_table->ant_cnt[i] == 0) {
				pfat_table->ant_ave[i] = 0;
			} else {
				pfat_table->ant_ave[i] =
					pfat_table->ant_sum[i] /
					pfat_table->ant_cnt[i];
				bpkt_filter_match = true;
			}

			if (pfat_table->ant_ave[i] > max_rssi) {
				max_rssi = pfat_table->ant_ave[i];
				target_ant = (u8) i;
			}
		}

		if (bpkt_filter_match == false) {
			rtl_set_bbreg(hw, DM_REG_TXAGC_A_1_MCS32_11N,
				      BIT(16), 0);
			rtl_set_bbreg(hw, DM_REG_IGI_A_11N, BIT(7), 0);
		} else {
			rtl_set_bbreg(hw, DM_REG_TXAGC_A_1_MCS32_11N,
				      BIT(16), 0);
			rtl_set_bbreg(hw, DM_REG_RX_ANT_CTRL_11N, BIT(8) |
				      BIT(7) | BIT(6), target_ant);
			rtl_set_bbreg(hw, DM_REG_TX_ANT_CTRL_11N,
				      BIT(21), 1);

			pfat_table->antsel_a[pfat_table->train_idx] =
				target_ant & BIT(0);
			pfat_table->antsel_b[pfat_table->train_idx] =
				(target_ant & BIT(1)) >> 1;
			pfat_table->antsel_c[pfat_table->train_idx] =
				(target_ant & BIT(2)) >> 2;

			if (target_ant == 0)
				rtl_set_bbreg(hw, DM_REG_IGI_A_11N, BIT(7), 0);
		}

		for (i = 0; i < 7; i++) {
			pfat_table->ant_sum[i] = 0;
			pfat_table->ant_cnt[i] = 0;
		}

		pfat_table->fat_state = FAT_NORMAL_STATE;
		return;
	}

	if (pfat_table->fat_state == FAT_NORMAL_STATE) {
		rtl88e_set_next_mac_address_target(hw);

		pfat_table->fat_state = FAT_TRAINING_STATE;
		rtl_set_bbreg(hw, DM_REG_TXAGC_A_1_MCS32_11N, BIT(16), 1);
		rtl_set_bbreg(hw, DM_REG_IGI_A_11N, BIT(7), 1);

		mod_timer(&rtlpriv->works.fast_antenna_training_timer,
			  jiffies + MSECS(RTL_WATCH_DOG_TIME));
	}
}