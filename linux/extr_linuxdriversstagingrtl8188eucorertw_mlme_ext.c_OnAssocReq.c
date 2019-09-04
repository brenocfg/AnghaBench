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
struct recv_frame {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 unsigned int _FAIL ; 

__attribute__((used)) static unsigned int OnAssocReq(struct adapter *padapter,
			       struct recv_frame *precv_frame)
{
#ifdef CONFIG_88EU_AP_MODE
	u16 capab_info;
	struct rtw_ieee802_11_elems elems;
	struct sta_info	*pstat;
	unsigned char		reassoc, *p, *pos, *wpa_ie;
	unsigned char WMM_IE[] = {0x00, 0x50, 0xf2, 0x02, 0x00, 0x01};
	int		i, wpa_ie_len, left;
	unsigned char		supportRate[16];
	int					supportRateNum;
	unsigned short		status = _STATS_SUCCESSFUL_;
	unsigned short		frame_type, ie_offset = 0;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct security_priv *psecuritypriv = &padapter->securitypriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	struct wlan_bssid_ex *cur = &(pmlmeinfo->network);
	struct sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->pkt->data;
	uint ie_len, pkt_len = precv_frame->pkt->len;

	if ((pmlmeinfo->state&0x03) != WIFI_FW_AP_STATE)
		return _FAIL;

	frame_type = GetFrameSubType(pframe);
	if (frame_type == WIFI_ASSOCREQ) {
		reassoc = 0;
		ie_offset = _ASOCREQ_IE_OFFSET_;
	} else { /*  WIFI_REASSOCREQ */
		reassoc = 1;
		ie_offset = _REASOCREQ_IE_OFFSET_;
	}

	if (pkt_len < IEEE80211_3ADDR_LEN + ie_offset) {
		DBG_88E("handle_assoc(reassoc=%d) - too short payload (len=%lu)"
		       "\n", reassoc, (unsigned long)pkt_len);
		return _FAIL;
	}

	pstat = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
	if (!pstat) {
		status = _RSON_CLS2_;
		goto asoc_class2_error;
	}

	capab_info = get_unaligned_le16(pframe + WLAN_HDR_A3_LEN);

	left = pkt_len - (IEEE80211_3ADDR_LEN + ie_offset);
	pos = pframe + (IEEE80211_3ADDR_LEN + ie_offset);

	DBG_88E("%s\n", __func__);

	/*  check if this stat has been successfully authenticated/assocated */
	if (!((pstat->state) & WIFI_FW_AUTH_SUCCESS)) {
		if (!((pstat->state) & WIFI_FW_ASSOC_SUCCESS)) {
			status = _RSON_CLS2_;
			goto asoc_class2_error;
		} else {
			pstat->state &= (~WIFI_FW_ASSOC_SUCCESS);
			pstat->state |= WIFI_FW_ASSOC_STATE;
		}
	} else {
		pstat->state &= (~WIFI_FW_AUTH_SUCCESS);
		pstat->state |= WIFI_FW_ASSOC_STATE;
	}
	pstat->capability = capab_info;
	/* now parse all ieee802_11 ie to point to elems */
	if (rtw_ieee802_11_parse_elems(pos, left, &elems, 1) == ParseFailed ||
	    !elems.ssid) {
		DBG_88E("STA %pM sent invalid association request\n",
			pstat->hwaddr);
		status = _STATS_FAILURE_;
		goto OnAssocReqFail;
	}

	/*  now we should check all the fields... */
	/*  checking SSID */
	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, _SSID_IE_, &ie_len,
		pkt_len - WLAN_HDR_A3_LEN - ie_offset);
	if (!p)
		status = _STATS_FAILURE_;

	if (ie_len == 0) { /*  broadcast ssid, however it is not allowed in assocreq */
		status = _STATS_FAILURE_;
	} else {
		/*  check if ssid match */
		if (memcmp((void *)(p+2), cur->Ssid.Ssid, cur->Ssid.SsidLength))
			status = _STATS_FAILURE_;

		if (ie_len != cur->Ssid.SsidLength)
			status = _STATS_FAILURE_;
	}

	if (_STATS_SUCCESSFUL_ != status)
		goto OnAssocReqFail;

	/*  check if the supported rate is ok */
	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, _SUPPORTEDRATES_IE_, &ie_len, pkt_len - WLAN_HDR_A3_LEN - ie_offset);
	if (p == NULL) {
		DBG_88E("Rx a sta assoc-req which supported rate is empty!\n");
		/*  use our own rate set as statoin used */
		/* memcpy(supportRate, AP_BSSRATE, AP_BSSRATE_LEN); */
		/* supportRateNum = AP_BSSRATE_LEN; */

		status = _STATS_FAILURE_;
		goto OnAssocReqFail;
	} else {
		memcpy(supportRate, p+2, ie_len);
		supportRateNum = ie_len;

		p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, _EXT_SUPPORTEDRATES_IE_, &ie_len,
				pkt_len - WLAN_HDR_A3_LEN - ie_offset);
		if (p !=  NULL) {
			if (supportRateNum <= sizeof(supportRate)) {
				memcpy(supportRate+supportRateNum, p+2, ie_len);
				supportRateNum += ie_len;
			}
		}
	}

	/* todo: mask supportRate between AP & STA -> move to update raid */
	/* get_matched_rate(pmlmeext, supportRate, &supportRateNum, 0); */

	/* update station supportRate */
	pstat->bssratelen = supportRateNum;
	memcpy(pstat->bssrateset, supportRate, supportRateNum);
	UpdateBrateTblForSoftAP(pstat->bssrateset, pstat->bssratelen);

	/* check RSN/WPA/WPS */
	pstat->dot8021xalg = 0;
	pstat->wpa_psk = 0;
	pstat->wpa_group_cipher = 0;
	pstat->wpa2_group_cipher = 0;
	pstat->wpa_pairwise_cipher = 0;
	pstat->wpa2_pairwise_cipher = 0;
	memset(pstat->wpa_ie, 0, sizeof(pstat->wpa_ie));
	if ((psecuritypriv->wpa_psk & BIT(1)) && elems.rsn_ie) {
		int group_cipher = 0, pairwise_cipher = 0;

		wpa_ie = elems.rsn_ie;
		wpa_ie_len = elems.rsn_ie_len;

		if (rtw_parse_wpa2_ie(wpa_ie-2, wpa_ie_len+2, &group_cipher, &pairwise_cipher, NULL) == _SUCCESS) {
			pstat->dot8021xalg = 1;/* psk,  todo:802.1x */
			pstat->wpa_psk |= BIT(1);

			pstat->wpa2_group_cipher = group_cipher&psecuritypriv->wpa2_group_cipher;
			pstat->wpa2_pairwise_cipher = pairwise_cipher&psecuritypriv->wpa2_pairwise_cipher;

			if (!pstat->wpa2_group_cipher)
				status = WLAN_STATUS_INVALID_GROUP_CIPHER;

			if (!pstat->wpa2_pairwise_cipher)
				status = WLAN_STATUS_INVALID_PAIRWISE_CIPHER;
		} else {
			status = WLAN_STATUS_INVALID_IE;
		}
	} else if ((psecuritypriv->wpa_psk & BIT(0)) && elems.wpa_ie) {
		int group_cipher = 0, pairwise_cipher = 0;

		wpa_ie = elems.wpa_ie;
		wpa_ie_len = elems.wpa_ie_len;

		if (rtw_parse_wpa_ie(wpa_ie-2, wpa_ie_len+2, &group_cipher, &pairwise_cipher, NULL) == _SUCCESS) {
			pstat->dot8021xalg = 1;/* psk,  todo:802.1x */
			pstat->wpa_psk |= BIT(0);

			pstat->wpa_group_cipher = group_cipher&psecuritypriv->wpa_group_cipher;
			pstat->wpa_pairwise_cipher = pairwise_cipher&psecuritypriv->wpa_pairwise_cipher;

			if (!pstat->wpa_group_cipher)
				status = WLAN_STATUS_INVALID_GROUP_CIPHER;

			if (!pstat->wpa_pairwise_cipher)
				status = WLAN_STATUS_INVALID_PAIRWISE_CIPHER;
		} else {
			status = WLAN_STATUS_INVALID_IE;
		}
	} else {
		wpa_ie = NULL;
		wpa_ie_len = 0;
	}

	if (_STATS_SUCCESSFUL_ != status)
		goto OnAssocReqFail;

	pstat->flags &= ~(WLAN_STA_WPS | WLAN_STA_MAYBE_WPS);
	if (!wpa_ie) {
		if (elems.wps_ie) {
			DBG_88E("STA included WPS IE in "
				   "(Re)Association Request - assume WPS is "
				   "used\n");
			pstat->flags |= WLAN_STA_WPS;
			/* wpabuf_free(sta->wps_ie); */
			/* sta->wps_ie = wpabuf_alloc_copy(elems.wps_ie + 4, */
			/*				elems.wps_ie_len - 4); */
		} else {
			DBG_88E("STA did not include WPA/RSN IE "
				   "in (Re)Association Request - possible WPS "
				   "use\n");
			pstat->flags |= WLAN_STA_MAYBE_WPS;
		}

		/*  AP support WPA/RSN, and sta is going to do WPS, but AP is not ready */
		/*  that the selected registrar of AP is _FLASE */
		if ((psecuritypriv->wpa_psk > 0) && (pstat->flags & (WLAN_STA_WPS|WLAN_STA_MAYBE_WPS))) {
			if (pmlmepriv->wps_beacon_ie) {
				u8 selected_registrar = 0;

				rtw_get_wps_attr_content(pmlmepriv->wps_beacon_ie, pmlmepriv->wps_beacon_ie_len, WPS_ATTR_SELECTED_REGISTRAR, &selected_registrar, NULL);

				if (!selected_registrar) {
					DBG_88E("selected_registrar is false , or AP is not ready to do WPS\n");

					status = _STATS_UNABLE_HANDLE_STA_;

					goto OnAssocReqFail;
				}
			}
		}
	} else {
		int copy_len;

		if (psecuritypriv->wpa_psk == 0) {
			DBG_88E("STA %pM: WPA/RSN IE in association "
			"request, but AP don't support WPA/RSN\n", pstat->hwaddr);

			status = WLAN_STATUS_INVALID_IE;

			goto OnAssocReqFail;
		}

		if (elems.wps_ie) {
			DBG_88E("STA included WPS IE in "
				   "(Re)Association Request - WPS is "
				   "used\n");
			pstat->flags |= WLAN_STA_WPS;
			copy_len = 0;
		} else {
			copy_len = min_t(int, wpa_ie_len + 2, sizeof(pstat->wpa_ie));
		}
		if (copy_len > 0)
			memcpy(pstat->wpa_ie, wpa_ie-2, copy_len);
	}
	/*  check if there is WMM IE & support WWM-PS */
	pstat->flags &= ~WLAN_STA_WME;
	pstat->qos_option = 0;
	pstat->qos_info = 0;
	pstat->has_legacy_ac = true;
	pstat->uapsd_vo = 0;
	pstat->uapsd_vi = 0;
	pstat->uapsd_be = 0;
	pstat->uapsd_bk = 0;
	if (pmlmepriv->qospriv.qos_option) {
		p = pframe + WLAN_HDR_A3_LEN + ie_offset; ie_len = 0;
		for (;;) {
			p = rtw_get_ie(p, _VENDOR_SPECIFIC_IE_, &ie_len, pkt_len - WLAN_HDR_A3_LEN - ie_offset);
			if (p != NULL) {
				if (!memcmp(p+2, WMM_IE, 6)) {
					pstat->flags |= WLAN_STA_WME;

					pstat->qos_option = 1;
					pstat->qos_info = *(p+8);

					pstat->max_sp_len = (pstat->qos_info>>5)&0x3;

					if ((pstat->qos_info&0xf) != 0xf)
						pstat->has_legacy_ac = true;
					else
						pstat->has_legacy_ac = false;

					if (pstat->qos_info&0xf) {
						if (pstat->qos_info&BIT(0))
							pstat->uapsd_vo = BIT(0)|BIT(1);
						else
							pstat->uapsd_vo = 0;

						if (pstat->qos_info&BIT(1))
							pstat->uapsd_vi = BIT(0)|BIT(1);
						else
							pstat->uapsd_vi = 0;

						if (pstat->qos_info&BIT(2))
							pstat->uapsd_bk = BIT(0)|BIT(1);
						else
							pstat->uapsd_bk = 0;

						if (pstat->qos_info&BIT(3))
							pstat->uapsd_be = BIT(0)|BIT(1);
						else
							pstat->uapsd_be = 0;
					}
					break;
				}
			} else {
				break;
			}
			p = p + ie_len + 2;
		}
	}

	/* save HT capabilities in the sta object */
	memset(&pstat->htpriv.ht_cap, 0, sizeof(struct ieee80211_ht_cap));
	if (elems.ht_capabilities &&
	    elems.ht_capabilities_len >= sizeof(struct ieee80211_ht_cap)) {
		pstat->flags |= WLAN_STA_HT;

		pstat->flags |= WLAN_STA_WME;

		memcpy(&pstat->htpriv.ht_cap,
		       elems.ht_capabilities, sizeof(struct ieee80211_ht_cap));
	} else {
		pstat->flags &= ~WLAN_STA_HT;
	}
	if ((!pmlmepriv->htpriv.ht_option) && (pstat->flags&WLAN_STA_HT)) {
		status = _STATS_FAILURE_;
		goto OnAssocReqFail;
	}

	if ((pstat->flags & WLAN_STA_HT) &&
	    ((pstat->wpa2_pairwise_cipher&WPA_CIPHER_TKIP) ||
	    (pstat->wpa_pairwise_cipher&WPA_CIPHER_TKIP))) {
		DBG_88E("HT: %pM tried to "
			"use TKIP with HT association\n", pstat->hwaddr);

		/* status = WLAN_STATUS_CIPHER_REJECTED_PER_POLICY; */
		/* goto OnAssocReqFail; */
	}

	pstat->flags |= WLAN_STA_NONERP;
	for (i = 0; i < pstat->bssratelen; i++) {
		if ((pstat->bssrateset[i] & 0x7f) > 22) {
			pstat->flags &= ~WLAN_STA_NONERP;
			break;
		}
	}

	if (pstat->capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
		pstat->flags |= WLAN_STA_SHORT_PREAMBLE;
	else
		pstat->flags &= ~WLAN_STA_SHORT_PREAMBLE;

	if (status != _STATS_SUCCESSFUL_)
		goto OnAssocReqFail;

	/* TODO: identify_proprietary_vendor_ie(); */
	/*  Realtek proprietary IE */
	/*  identify if this is Broadcom sta */
	/*  identify if this is ralink sta */
	/*  Customer proprietary IE */

	/* get a unique AID */
	if (pstat->aid > 0) {
		DBG_88E("  old AID %d\n", pstat->aid);
	} else {
		for (pstat->aid = 1; pstat->aid <= NUM_STA; pstat->aid++)
			if (pstapriv->sta_aid[pstat->aid - 1] == NULL)
				break;

		/* if (pstat->aid > NUM_STA) { */
		if (pstat->aid > pstapriv->max_num_sta) {
			pstat->aid = 0;

			DBG_88E("  no room for more AIDs\n");

			status = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;

			goto OnAssocReqFail;
		} else {
			pstapriv->sta_aid[pstat->aid - 1] = pstat;
			DBG_88E("allocate new AID=(%d)\n", pstat->aid);
		}
	}

	pstat->state &= (~WIFI_FW_ASSOC_STATE);
	pstat->state |= WIFI_FW_ASSOC_SUCCESS;

	spin_lock_bh(&pstapriv->auth_list_lock);
	if (!list_empty(&pstat->auth_list)) {
		list_del_init(&pstat->auth_list);
		pstapriv->auth_list_cnt--;
	}
	spin_unlock_bh(&pstapriv->auth_list_lock);

	spin_lock_bh(&pstapriv->asoc_list_lock);
	if (list_empty(&pstat->asoc_list)) {
		pstat->expire_to = pstapriv->expire_to;
		list_add_tail(&pstat->asoc_list, &pstapriv->asoc_list);
		pstapriv->asoc_list_cnt++;
	}
	spin_unlock_bh(&pstapriv->asoc_list_lock);

	/*  now the station is qualified to join our BSS... */
	if ((pstat->state & WIFI_FW_ASSOC_SUCCESS) && (_STATS_SUCCESSFUL_ == status)) {
		/* 1 bss_cap_update & sta_info_update */
		bss_cap_update_on_sta_join(padapter, pstat);
		sta_info_update(padapter, pstat);

		/* issue assoc rsp before notify station join event. */
		if (frame_type == WIFI_ASSOCREQ)
			issue_asocrsp(padapter, status, pstat, WIFI_ASSOCRSP);
		else
			issue_asocrsp(padapter, status, pstat, WIFI_REASSOCRSP);

		/* 2 - report to upper layer */
		DBG_88E("indicate_sta_join_event to upper layer - hostapd\n");
		rtw_indicate_sta_assoc_event(padapter, pstat);

		/* 3-(1) report sta add event */
		report_add_sta_event(padapter, pstat->hwaddr, pstat->aid);
	}

	return _SUCCESS;

asoc_class2_error:

	issue_deauth(padapter, (void *)GetAddr2Ptr(pframe), status);

	return _FAIL;

OnAssocReqFail:

	pstat->aid = 0;
	if (frame_type == WIFI_ASSOCREQ)
		issue_asocrsp(padapter, status, pstat, WIFI_ASSOCRSP);
	else
		issue_asocrsp(padapter, status, pstat, WIFI_REASSOCRSP);

#endif /* CONFIG_88EU_AP_MODE */

	return _FAIL;
}