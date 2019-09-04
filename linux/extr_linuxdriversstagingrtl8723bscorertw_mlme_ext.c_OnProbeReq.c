#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* rx_data; int len; } ;
struct TYPE_6__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int uint ;
typedef  int u8 ;
struct TYPE_7__ {int /*<<< orphan*/  SsidLength; scalar_t__ Ssid; } ;
struct wlan_bssid_ex {TYPE_3__ Ssid; } ;
struct TYPE_8__ {scalar_t__ join_res; } ;
struct mlme_priv {TYPE_4__ cur_network; } ;
struct mlme_ext_info {scalar_t__ hidden_ssid_mode; struct wlan_bssid_ex network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_AP_STATE ; 
 int WIFI_STATION_STATE ; 
 int WLAN_HDR_A3_LEN ; 
 int _FW_LINKED ; 
 int _PROBEREQ_IE_OFFSET_ ; 
 int /*<<< orphan*/  _SSID_IE_ ; 
 unsigned int _SUCCESS ; 
 int check_fwstate (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  get_sa (int*) ; 
 int /*<<< orphan*/  issue_probersp (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcmp (void*,void*,int /*<<< orphan*/ ) ; 
 unsigned char* rtw_get_ie (int*,int /*<<< orphan*/ ,int*,int) ; 

unsigned int OnProbeReq(struct adapter *padapter, union recv_frame *precv_frame)
{
	unsigned int	ielen;
	unsigned char *p;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	struct wlan_bssid_ex	*cur = &(pmlmeinfo->network);
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uint len = precv_frame->u.hdr.len;
	u8 is_valid_p2p_probereq = false;

	if (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		return _SUCCESS;

	if (check_fwstate(pmlmepriv, _FW_LINKED) == false &&
		check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE|WIFI_AP_STATE) == false) {
		return _SUCCESS;
	}


	/* DBG_871X("+OnProbeReq\n"); */

#ifdef CONFIG_AUTO_AP_MODE
	if (check_fwstate(pmlmepriv, _FW_LINKED) &&
			pmlmepriv->cur_network.join_res) {
		struct sta_info *psta;
		u8 *mac_addr, *peer_addr;
		struct sta_priv *pstapriv = &padapter->stapriv;
		u8 RC_OUI[4] = {0x00, 0xE0, 0x4C, 0x0A};
		/* EID[1] + EID_LEN[1] + RC_OUI[4] + MAC[6] + PairingID[2] + ChannelNum[2] */

		p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + _PROBEREQ_IE_OFFSET_, _VENDOR_SPECIFIC_IE_, (int *)&ielen,
			len - WLAN_HDR_A3_LEN - _PROBEREQ_IE_OFFSET_);

		if (!p || ielen != 14)
			goto _non_rc_device;

		if (memcmp(p+2, RC_OUI, sizeof(RC_OUI)))
			goto _non_rc_device;

		if (memcmp(p+6, get_sa(pframe), ETH_ALEN)) {
			DBG_871X("%s, do rc pairing ("MAC_FMT"), but mac addr mismatch!("MAC_FMT")\n", __func__,
				MAC_ARG(get_sa(pframe)), MAC_ARG(p+6));

			goto _non_rc_device;
		}

		DBG_871X("%s, got the pairing device("MAC_FMT")\n", __func__,  MAC_ARG(get_sa(pframe)));

		/* new a station */
		psta = rtw_get_stainfo(pstapriv, get_sa(pframe));
		if (psta == NULL) {
			/*  allocate a new one */
			DBG_871X("going to alloc stainfo for rc ="MAC_FMT"\n",  MAC_ARG(get_sa(pframe)));
			psta = rtw_alloc_stainfo(pstapriv, get_sa(pframe));
			if (psta == NULL) {
				/* TODO: */
				DBG_871X(" Exceed the upper limit of supported clients...\n");
				return _SUCCESS;
			}

			spin_lock_bh(&pstapriv->asoc_list_lock);
			if (list_empty(&psta->asoc_list)) {
				psta->expire_to = pstapriv->expire_to;
				list_add_tail(&psta->asoc_list, &pstapriv->asoc_list);
				pstapriv->asoc_list_cnt++;
			}
			spin_unlock_bh(&pstapriv->asoc_list_lock);

			/* generate pairing ID */
			mac_addr = myid(&(padapter->eeprompriv));
			peer_addr = psta->hwaddr;
			psta->pid = (u16)(((mac_addr[4]<<8) + mac_addr[5]) + ((peer_addr[4]<<8) + peer_addr[5]));

			/* update peer stainfo */
			psta->isrc = true;
			/* psta->aid = 0; */
			/* psta->mac_id = 2; */

			/* get a unique AID */
			if (psta->aid > 0) {
				DBG_871X("old AID %d\n", psta->aid);
			} else {
				for (psta->aid = 1; psta->aid <= NUM_STA; psta->aid++)
					if (pstapriv->sta_aid[psta->aid - 1] == NULL)
						break;

				if (psta->aid > pstapriv->max_num_sta) {
					psta->aid = 0;
					DBG_871X("no room for more AIDs\n");
					return _SUCCESS;
				} else {
					pstapriv->sta_aid[psta->aid - 1] = psta;
					DBG_871X("allocate new AID = (%d)\n", psta->aid);
				}
			}

			psta->qos_option = 1;
			psta->bw_mode = CHANNEL_WIDTH_20;
			psta->ieee8021x_blocked = false;
			psta->htpriv.ht_option = true;
			psta->htpriv.ampdu_enable = false;
			psta->htpriv.sgi_20m = false;
			psta->htpriv.sgi_40m = false;
			psta->htpriv.ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
			psta->htpriv.agg_enable_bitmap = 0x0;/* reset */
			psta->htpriv.candidate_tid_bitmap = 0x0;/* reset */

			rtw_hal_set_odm_var(padapter, HAL_ODM_STA_INFO, psta, true);

			memset((void *)&psta->sta_stats, 0, sizeof(struct stainfo_stats));

			spin_lock_bh(&psta->lock);
			psta->state |= _FW_LINKED;
			spin_unlock_bh(&psta->lock);

			report_add_sta_event(padapter, psta->hwaddr, psta->aid);

		}

		issue_probersp(padapter, get_sa(pframe), false);

		return _SUCCESS;

	}

_non_rc_device:

	return _SUCCESS;

#endif /* CONFIG_AUTO_AP_MODE */

	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + _PROBEREQ_IE_OFFSET_, _SSID_IE_, (int *)&ielen,
			len - WLAN_HDR_A3_LEN - _PROBEREQ_IE_OFFSET_);


	/* check (wildcard) SSID */
	if (p != NULL) {
		if (is_valid_p2p_probereq)
			goto _issue_probersp;

		if ((ielen != 0 && false == !memcmp((void *)(p+2), (void *)cur->Ssid.Ssid, cur->Ssid.SsidLength))
			|| (ielen == 0 && pmlmeinfo->hidden_ssid_mode)
		)
			return _SUCCESS;

_issue_probersp:
		if ((check_fwstate(pmlmepriv, _FW_LINKED)  &&
			pmlmepriv->cur_network.join_res) || check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) {
			/* DBG_871X("+issue_probersp during ap mode\n"); */
			issue_probersp(padapter, get_sa(pframe), is_valid_p2p_probereq);
		}

	}

	return _SUCCESS;

}