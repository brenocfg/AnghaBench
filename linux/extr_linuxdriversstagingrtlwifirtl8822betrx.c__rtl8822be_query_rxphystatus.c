#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct rtl_stats {int /*<<< orphan*/  rx_pwdb_all; scalar_t__ signalstrength; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct rtl_priv {TYPE_2__ phydm; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* phydm_query_phy_status ) (struct rtl_priv*,scalar_t__*,struct ieee80211_hdr*,struct rtl_stats*) ;} ;

/* Variables and functions */
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ rtl_signal_scale_mapping (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rtl_priv*,scalar_t__*,struct ieee80211_hdr*,struct rtl_stats*) ; 

__attribute__((used)) static void _rtl8822be_query_rxphystatus(struct ieee80211_hw *hw, u8 *phystrpt,
					 struct ieee80211_hdr *hdr,
					 struct rtl_stats *pstatus)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->phydm.ops->phydm_query_phy_status(rtlpriv, phystrpt, hdr,
						   pstatus);

	/* UI BSS List signal strength(in percentage),
	 * make it good looking, from 0~100.
	 */
	pstatus->signalstrength =
		(u8)(rtl_signal_scale_mapping(hw, pstatus->rx_pwdb_all));
}