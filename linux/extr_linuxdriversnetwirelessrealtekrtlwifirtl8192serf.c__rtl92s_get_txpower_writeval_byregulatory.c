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
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ dynamic_txhighpower_lvl; } ;
struct rtl_phy {int** mcs_offset; int pwrgroup_cnt; int /*<<< orphan*/  current_chan_bw; } ;
struct rtl_priv {TYPE_1__ dm; struct rtl_phy phy; } ;
struct rtl_efuse {int eeprom_regulatory; int** pwrgroup_ht40; int** pwrgroup_ht20; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  HT_CHANNEL_WIDTH_20_40 ; 
 size_t RF90_PATH_A ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ TX_HIGH_PWR_LEVEL_LEVEL1 ; 
 scalar_t__ TX_HIGH_PWR_LEVEL_LEVEL2 ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92s_get_txpower_writeval_byregulatory(struct ieee80211_hw *hw,
						      u8 chnl, u8 index,
						      u32 pwrbase0,
						      u32 pwrbase1,
						      u32 *p_outwrite_val)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 i, chnlgroup, pwrdiff_limit[4];
	u32 writeval, customer_limit;

	/* Index 0 & 1= legacy OFDM, 2-5=HT_MCS rate */
	switch (rtlefuse->eeprom_regulatory) {
	case 0:
		/* Realtek better performance increase power diff
		 * defined by Realtek for large power */
		chnlgroup = 0;

		writeval = rtlphy->mcs_offset[chnlgroup][index] +
				((index < 2) ? pwrbase0 : pwrbase1);

		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "RTK better performance, writeval = 0x%x\n", writeval);
		break;
	case 1:
		/* Realtek regulatory increase power diff defined
		 * by Realtek for regulatory */
		if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) {
			writeval = ((index < 2) ? pwrbase0 : pwrbase1);

			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
				 "Realtek regulatory, 40MHz, writeval = 0x%x\n",
				 writeval);
		} else {
			chnlgroup = 0;

			if (rtlphy->pwrgroup_cnt >= 3) {
				if (chnl <= 3)
					chnlgroup = 0;
				else if (chnl >= 4 && chnl <= 8)
					chnlgroup = 1;
				else if (chnl > 8)
					chnlgroup = 2;
				if (rtlphy->pwrgroup_cnt == 4)
					chnlgroup++;
			}

			writeval = rtlphy->mcs_offset[chnlgroup][index]
					+ ((index < 2) ?
					pwrbase0 : pwrbase1);

			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
				 "Realtek regulatory, 20MHz, writeval = 0x%x\n",
				 writeval);
		}
		break;
	case 2:
		/* Better regulatory don't increase any power diff */
		writeval = ((index < 2) ? pwrbase0 : pwrbase1);
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "Better regulatory, writeval = 0x%x\n", writeval);
		break;
	case 3:
		/* Customer defined power diff. increase power diff
		  defined by customer. */
		chnlgroup = 0;

		if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) {
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
				 "customer's limit, 40MHz = 0x%x\n",
				 rtlefuse->pwrgroup_ht40
				 [RF90_PATH_A][chnl - 1]);
		} else {
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
				 "customer's limit, 20MHz = 0x%x\n",
				 rtlefuse->pwrgroup_ht20
				 [RF90_PATH_A][chnl - 1]);
		}

		for (i = 0; i < 4; i++) {
			pwrdiff_limit[i] = (u8)((rtlphy->mcs_offset
				[chnlgroup][index] & (0x7f << (i * 8)))
				>> (i * 8));

			if (rtlphy->current_chan_bw ==
			    HT_CHANNEL_WIDTH_20_40) {
				if (pwrdiff_limit[i] >
				    rtlefuse->pwrgroup_ht40
				    [RF90_PATH_A][chnl - 1]) {
					pwrdiff_limit[i] =
					  rtlefuse->pwrgroup_ht40
					  [RF90_PATH_A][chnl - 1];
				}
			} else {
				if (pwrdiff_limit[i] >
				    rtlefuse->pwrgroup_ht20
				    [RF90_PATH_A][chnl - 1]) {
					pwrdiff_limit[i] =
					    rtlefuse->pwrgroup_ht20
					    [RF90_PATH_A][chnl - 1];
				}
			}
		}

		customer_limit = (pwrdiff_limit[3] << 24) |
				(pwrdiff_limit[2] << 16) |
				(pwrdiff_limit[1] << 8) |
				(pwrdiff_limit[0]);
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "Customer's limit = 0x%x\n", customer_limit);

		writeval = customer_limit + ((index < 2) ?
					     pwrbase0 : pwrbase1);
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "Customer, writeval = 0x%x\n", writeval);
		break;
	default:
		chnlgroup = 0;
		writeval = rtlphy->mcs_offset[chnlgroup][index] +
				((index < 2) ? pwrbase0 : pwrbase1);
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "RTK better performance, writeval = 0x%x\n", writeval);
		break;
	}

	if (rtlpriv->dm.dynamic_txhighpower_lvl == TX_HIGH_PWR_LEVEL_LEVEL1)
		writeval = 0x10101010;
	else if (rtlpriv->dm.dynamic_txhighpower_lvl ==
		 TX_HIGH_PWR_LEVEL_LEVEL2)
		writeval = 0x0;

	*p_outwrite_val = writeval;

}