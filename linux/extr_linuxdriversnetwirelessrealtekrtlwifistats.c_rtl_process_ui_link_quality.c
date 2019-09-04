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
typedef  int u32 ;
struct rtl_stats {scalar_t__ signalquality; int* rx_mimo_sig_qual; } ;
struct TYPE_3__ {size_t total_num; int* elements; size_t index; int total_val; } ;
struct TYPE_4__ {int signal_quality; int last_sigstrength_inpercent; int* rx_evm_percentage; TYPE_1__ ui_link_quality; } ;
struct rtl_priv {TYPE_2__ stats; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t PHY_LINKQUALITY_SLID_WIN_MAX ; 
 int RX_SMOOTH_FACTOR ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl_process_ui_link_quality(struct ieee80211_hw *hw,
					struct rtl_stats *pstatus)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 last_evm, n_stream, tmpval;

	if (pstatus->signalquality == 0)
		return;

	if (rtlpriv->stats.ui_link_quality.total_num++ >=
	    PHY_LINKQUALITY_SLID_WIN_MAX) {
		rtlpriv->stats.ui_link_quality.total_num =
		    PHY_LINKQUALITY_SLID_WIN_MAX;
		last_evm = rtlpriv->stats.ui_link_quality.elements[
			rtlpriv->stats.ui_link_quality.index];
		rtlpriv->stats.ui_link_quality.total_val -= last_evm;
	}
	rtlpriv->stats.ui_link_quality.total_val += pstatus->signalquality;
	rtlpriv->stats.ui_link_quality.elements[
		rtlpriv->stats.ui_link_quality.index++] =
							pstatus->signalquality;
	if (rtlpriv->stats.ui_link_quality.index >=
	    PHY_LINKQUALITY_SLID_WIN_MAX)
		rtlpriv->stats.ui_link_quality.index = 0;
	tmpval = rtlpriv->stats.ui_link_quality.total_val /
	    rtlpriv->stats.ui_link_quality.total_num;
	rtlpriv->stats.signal_quality = tmpval;
	rtlpriv->stats.last_sigstrength_inpercent = tmpval;
	for (n_stream = 0; n_stream < 2; n_stream++) {
		if (pstatus->rx_mimo_sig_qual[n_stream] != -1) {
			if (rtlpriv->stats.rx_evm_percentage[n_stream] == 0) {
				rtlpriv->stats.rx_evm_percentage[n_stream] =
				    pstatus->rx_mimo_sig_qual[n_stream];
			}
			rtlpriv->stats.rx_evm_percentage[n_stream] =
			    ((rtlpriv->stats.rx_evm_percentage[n_stream]
			      * (RX_SMOOTH_FACTOR - 1)) +
			     (pstatus->rx_mimo_sig_qual[n_stream] * 1)) /
			    (RX_SMOOTH_FACTOR);
		}
	}
}