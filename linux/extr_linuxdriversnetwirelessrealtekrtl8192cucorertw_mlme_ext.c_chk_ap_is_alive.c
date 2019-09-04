#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int dummy; } ;
struct mlme_ext_info {int dummy; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_3__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _TRUE ; 
 scalar_t__ sta_last_rx_beacon_pkts (struct sta_info*) ; 
 scalar_t__ sta_last_rx_data_pkts (struct sta_info*) ; 
 scalar_t__ sta_last_rx_probersp_pkts (struct sta_info*) ; 
 scalar_t__ sta_rx_beacon_pkts (struct sta_info*) ; 
 scalar_t__ sta_rx_data_pkts (struct sta_info*) ; 
 scalar_t__ sta_rx_probersp_pkts (struct sta_info*) ; 
 int /*<<< orphan*/  sta_update_last_rx_pkts (struct sta_info*) ; 

u8 chk_ap_is_alive(_adapter *padapter, struct sta_info *psta)
{
	u8 ret = _FALSE;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	#ifdef DBG_EXPIRATION_CHK
	DBG_871X(FUNC_ADPT_FMT" rx:"STA_PKTS_FMT", beacon:%llu, probersp_to_self:%llu"
				/*", probersp_bm:%llu, probersp_uo:%llu, probereq:%llu, BI:%u"*/
				", retry:%u\n"
		, FUNC_ADPT_ARG(padapter)
		, STA_RX_PKTS_DIFF_ARG(psta)
		, psta->sta_stats.rx_beacon_pkts - psta->sta_stats.last_rx_beacon_pkts
		, psta->sta_stats.rx_probersp_pkts - psta->sta_stats.last_rx_probersp_pkts
		/*, psta->sta_stats.rx_probersp_bm_pkts - psta->sta_stats.last_rx_probersp_bm_pkts
		, psta->sta_stats.rx_probersp_uo_pkts - psta->sta_stats.last_rx_probersp_uo_pkts
		, psta->sta_stats.rx_probereq_pkts - psta->sta_stats.last_rx_probereq_pkts
		, pmlmeinfo->bcn_interval*/
		, pmlmeext->retry
	);

	DBG_871X(FUNC_ADPT_FMT" tx_pkts:%llu, link_count:%u\n", FUNC_ADPT_ARG(padapter)
		, padapter->xmitpriv.tx_pkts
		, pmlmeinfo->link_count
	);
	#endif

	if((sta_rx_data_pkts(psta) == sta_last_rx_data_pkts(psta))
		&& sta_rx_beacon_pkts(psta) == sta_last_rx_beacon_pkts(psta)
		&& sta_rx_probersp_pkts(psta) == sta_last_rx_probersp_pkts(psta)
	)
	{
		ret = _FALSE;
	}
	else
	{
		ret = _TRUE;
	}

	sta_update_last_rx_pkts(psta);

	return ret;
}