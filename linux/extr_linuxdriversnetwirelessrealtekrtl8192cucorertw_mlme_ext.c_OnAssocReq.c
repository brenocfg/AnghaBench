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
typedef  union recv_frame {int dummy; } recv_frame ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 unsigned int _FAIL ; 

unsigned int OnAssocReq(_adapter *padapter, union recv_frame *precv_frame)
{
#ifdef CONFIG_AP_MODE
	_irqL irqL;
	u16 capab_info, listen_interval;
	struct rtw_ieee802_11_elems elems;	
	struct sta_info	*pstat;
	unsigned char		reassoc, *p, *pos, *wpa_ie;
	unsigned char WMM_IE[] = {0x00, 0x50, 0xf2, 0x02, 0x00, 0x01};
	int		i, ie_len, wpa_ie_len, left;
	unsigned char		supportRate[16];
	int					supportRateNum;
	unsigned short		status = _STATS_SUCCESSFUL_;
	unsigned short		frame_type, ie_offset=0;	
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct security_priv *psecuritypriv = &padapter->securitypriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);	
	WLAN_BSSID_EX 	*cur = &(pmlmeinfo->network);
	struct sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uint pkt_len = precv_frame->u.hdr.len;
#ifdef CONFIG_P2P
	struct wifidirect_info	*pwdinfo = &(padapter->wdinfo);
	u8 p2p_status_code = P2P_STATUS_SUCCESS;
	u8 *p2pie;
	u32 p2pielen = 0;
#ifdef CONFIG_WFD
	u8	wfd_ie[ 128 ] = { 0x00 };
	u32	wfd_ielen = 0;
#endif // CONFIG_WFD
#endif //CONFIG_P2P

#ifdef CONFIG_CONCURRENT_MODE
	if(((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE) &&
		check_buddy_fwstate(padapter, _FW_UNDER_LINKING|_FW_UNDER_SURVEY))
	{
		//don't process assoc request;
		return _SUCCESS;
	}
#endif //CONFIG_CONCURRENT_MODE

	if((pmlmeinfo->state&0x03) != WIFI_FW_AP_STATE)
		return _FAIL;
	
	frame_type = GetFrameSubType(pframe);
	if (frame_type == WIFI_ASSOCREQ)
	{
		reassoc = 0;
		ie_offset = _ASOCREQ_IE_OFFSET_;
	}	
	else // WIFI_REASSOCREQ
	{
		reassoc = 1;
		ie_offset = _REASOCREQ_IE_OFFSET_;
	}
	

	if (pkt_len < IEEE80211_3ADDR_LEN + ie_offset) {
		DBG_871X("handle_assoc(reassoc=%d) - too short payload (len=%lu)"
		       "\n", reassoc, (unsigned long)pkt_len);
		return _FAIL;
	}
	
	pstat = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
	if (pstat == (struct sta_info *)NULL)
	{
		status = _RSON_CLS2_;
		goto asoc_class2_error;
	}

	capab_info = RTW_GET_LE16(pframe + WLAN_HDR_A3_LEN);
	//capab_info = le16_to_cpu(*(unsigned short *)(pframe + WLAN_HDR_A3_LEN));	
	//listen_interval = le16_to_cpu(*(unsigned short *)(pframe + WLAN_HDR_A3_LEN+2));
	listen_interval = RTW_GET_LE16(pframe + WLAN_HDR_A3_LEN+2);

	left = pkt_len - (IEEE80211_3ADDR_LEN + ie_offset);
	pos = pframe + (IEEE80211_3ADDR_LEN + ie_offset);
	

	DBG_871X("%s\n", __FUNCTION__);

	// check if this stat has been successfully authenticated/assocated
	if (!((pstat->state) & WIFI_FW_AUTH_SUCCESS))
	{
		if (!((pstat->state) & WIFI_FW_ASSOC_SUCCESS))
		{
			status = _RSON_CLS2_;
			goto asoc_class2_error;
		}
		else
		{
			pstat->state &= (~WIFI_FW_ASSOC_SUCCESS);
			pstat->state |= WIFI_FW_ASSOC_STATE;				
		}
	}
	else
	{
		pstat->state &= (~WIFI_FW_AUTH_SUCCESS);
		pstat->state |= WIFI_FW_ASSOC_STATE;
	}


#if 0// todo:tkip_countermeasures
	if (hapd->tkip_countermeasures) {
		resp = WLAN_REASON_MICHAEL_MIC_FAILURE;
		goto fail;
	}
#endif

	pstat->capability = capab_info;

#if 0//todo:
	//check listen_interval
	if (listen_interval > hapd->conf->max_listen_interval) {
		hostapd_logger(hapd, mgmt->sa, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_DEBUG,
			       "Too large Listen Interval (%d)",
			       listen_interval);
		resp = WLAN_STATUS_ASSOC_DENIED_LISTEN_INT_TOO_LARGE;
		goto fail;
	}
	
	pstat->listen_interval = listen_interval;
#endif

	//now parse all ieee802_11 ie to point to elems
	if (rtw_ieee802_11_parse_elems(pos, left, &elems, 1) == ParseFailed ||
	    !elems.ssid) {
		DBG_871X("STA " MAC_FMT " sent invalid association request\n",
		       MAC_ARG(pstat->hwaddr));
		status = _STATS_FAILURE_;		
		goto OnAssocReqFail;
	}


	// now we should check all the fields...
	// checking SSID
	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, _SSID_IE_, &ie_len,
		pkt_len - WLAN_HDR_A3_LEN - ie_offset);
	if (p == NULL)
	{
		status = _STATS_FAILURE_;		
	}

	if (ie_len == 0) // broadcast ssid, however it is not allowed in assocreq
		status = _STATS_FAILURE_;
	else
	{
		// check if ssid match
		if (!_rtw_memcmp((void *)(p+2), cur->Ssid.Ssid, cur->Ssid.SsidLength))
			status = _STATS_FAILURE_;

		if (ie_len != cur->Ssid.SsidLength)
			status = _STATS_FAILURE_;
	}

	if(_STATS_SUCCESSFUL_ != status)
		goto OnAssocReqFail;

	// check if the supported rate is ok
	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, _SUPPORTEDRATES_IE_, &ie_len, pkt_len - WLAN_HDR_A3_LEN - ie_offset);
	if (p == NULL) {
		DBG_871X("Rx a sta assoc-req which supported rate is empty!\n");
		// use our own rate set as statoin used
		//_rtw_memcpy(supportRate, AP_BSSRATE, AP_BSSRATE_LEN);
		//supportRateNum = AP_BSSRATE_LEN;
		
		status = _STATS_FAILURE_;
		goto OnAssocReqFail;
	}
	else {
		_rtw_memcpy(supportRate, p+2, ie_len);
		supportRateNum = ie_len;

		p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, _EXT_SUPPORTEDRATES_IE_ , &ie_len,
				pkt_len - WLAN_HDR_A3_LEN - ie_offset);
		if (p !=  NULL) {
			
			if(supportRateNum<=sizeof(supportRate))
			{
				_rtw_memcpy(supportRate+supportRateNum, p+2, ie_len);
				supportRateNum += ie_len;
			}			
		}
	}

	//todo: mask supportRate between AP & STA -> move to update raid
	//get_matched_rate(pmlmeext, supportRate, &supportRateNum, 0);

	//update station supportRate	
	pstat->bssratelen = supportRateNum;
	_rtw_memcpy(pstat->bssrateset, supportRate, supportRateNum);


	//check RSN/WPA/WPS
	pstat->dot8021xalg = 0;
      	pstat->wpa_psk = 0;
	pstat->wpa_group_cipher = 0;
	pstat->wpa2_group_cipher = 0;
	pstat->wpa_pairwise_cipher = 0;
	pstat->wpa2_pairwise_cipher = 0;
	_rtw_memset(pstat->wpa_ie, 0, sizeof(pstat->wpa_ie));
	if((psecuritypriv->wpa_psk & BIT(1)) && elems.rsn_ie) {

		int group_cipher=0, pairwise_cipher=0;	
		
		wpa_ie = elems.rsn_ie;
		wpa_ie_len = elems.rsn_ie_len;

		if(rtw_parse_wpa2_ie(wpa_ie-2, wpa_ie_len+2, &group_cipher, &pairwise_cipher) == _SUCCESS)
		{
			pstat->dot8021xalg = 1;//psk,  todo:802.1x						
			pstat->wpa_psk |= BIT(1);

			pstat->wpa2_group_cipher = group_cipher&psecuritypriv->wpa2_group_cipher;				
			pstat->wpa2_pairwise_cipher = pairwise_cipher&psecuritypriv->wpa2_pairwise_cipher;
			
			if(!pstat->wpa2_group_cipher)
				status = WLAN_STATUS_GROUP_CIPHER_NOT_VALID;

			if(!pstat->wpa2_pairwise_cipher)
				status = WLAN_STATUS_PAIRWISE_CIPHER_NOT_VALID;
		}
		else
		{
			status = WLAN_STATUS_INVALID_IE;
		}	
			
	} else if ((psecuritypriv->wpa_psk & BIT(0)) && elems.wpa_ie) {

		int group_cipher=0, pairwise_cipher=0;	
		
		wpa_ie = elems.wpa_ie;
		wpa_ie_len = elems.wpa_ie_len;

		if(rtw_parse_wpa_ie(wpa_ie-2, wpa_ie_len+2, &group_cipher, &pairwise_cipher) == _SUCCESS)
		{
			pstat->dot8021xalg = 1;//psk,  todo:802.1x						
			pstat->wpa_psk |= BIT(0);

			pstat->wpa_group_cipher = group_cipher&psecuritypriv->wpa_group_cipher;				
			pstat->wpa_pairwise_cipher = pairwise_cipher&psecuritypriv->wpa_pairwise_cipher;
			
			if(!pstat->wpa_group_cipher)
				status = WLAN_STATUS_GROUP_CIPHER_NOT_VALID;

			if(!pstat->wpa_pairwise_cipher)
				status = WLAN_STATUS_PAIRWISE_CIPHER_NOT_VALID;
		
		}
		else
		{
			status = WLAN_STATUS_INVALID_IE;
		}
		
	} else {
		wpa_ie = NULL;
		wpa_ie_len = 0;
	}

	if(_STATS_SUCCESSFUL_ != status)
		goto OnAssocReqFail;

	pstat->flags &= ~(WLAN_STA_WPS | WLAN_STA_MAYBE_WPS);
	//if (hapd->conf->wps_state && wpa_ie == NULL) { //todo: to check ap if supporting WPS
	if(wpa_ie == NULL) {
		if (elems.wps_ie) {
			DBG_871X("STA included WPS IE in "
				   "(Re)Association Request - assume WPS is "
				   "used\n");
			pstat->flags |= WLAN_STA_WPS;
			//wpabuf_free(sta->wps_ie);
			//sta->wps_ie = wpabuf_alloc_copy(elems.wps_ie + 4,
			//				elems.wps_ie_len - 4);
		} else {
			DBG_871X("STA did not include WPA/RSN IE "
				   "in (Re)Association Request - possible WPS "
				   "use\n");
			pstat->flags |= WLAN_STA_MAYBE_WPS;
		}


		// AP support WPA/RSN, and sta is going to do WPS, but AP is not ready
		// that the selected registrar of AP is _FLASE
		if((psecuritypriv->wpa_psk >0)  
			&& (pstat->flags & (WLAN_STA_WPS|WLAN_STA_MAYBE_WPS)))
		{
			if(pmlmepriv->wps_beacon_ie)
			{	
				u8 selected_registrar = 0;
				
				rtw_get_wps_attr_content(pmlmepriv->wps_beacon_ie, pmlmepriv->wps_beacon_ie_len, WPS_ATTR_SELECTED_REGISTRAR , &selected_registrar, NULL);

				if(!selected_registrar)
				{						
					DBG_871X("selected_registrar is _FALSE , or AP is not ready to do WPS\n");
						
					status = _STATS_UNABLE_HANDLE_STA_;
			
					goto OnAssocReqFail;
				}						
			}			
		}
			
	}
	else
	{
		int copy_len;

		if(psecuritypriv->wpa_psk == 0)
		{
			DBG_871X("STA " MAC_FMT ": WPA/RSN IE in association "
		       	"request, but AP don't support WPA/RSN\n", MAC_ARG(pstat->hwaddr));
			
			status = WLAN_STATUS_INVALID_IE;
			
			goto OnAssocReqFail;

		}

		if (elems.wps_ie) {
			DBG_871X("STA included WPS IE in "
				   "(Re)Association Request - WPS is "
				   "used\n");
			pstat->flags |= WLAN_STA_WPS;
			copy_len=0;
		}
		else
		{
			copy_len = ((wpa_ie_len+2) > sizeof(pstat->wpa_ie)) ? (sizeof(pstat->wpa_ie)):(wpa_ie_len+2);
		}

		
		if(copy_len>0)
			_rtw_memcpy(pstat->wpa_ie, wpa_ie-2, copy_len);
		
	}


	// check if there is WMM IE & support WWM-PS
	pstat->flags &= ~WLAN_STA_WME;
	pstat->qos_option = 0;
	pstat->qos_info = 0;
	pstat->has_legacy_ac = _TRUE;
	pstat->uapsd_vo = 0;
	pstat->uapsd_vi = 0;
	pstat->uapsd_be = 0;
	pstat->uapsd_bk = 0;
	if (pmlmepriv->qospriv.qos_option) 
	{
		p = pframe + WLAN_HDR_A3_LEN + ie_offset; ie_len = 0;
		for (;;) 
		{
			p = rtw_get_ie(p, _VENDOR_SPECIFIC_IE_, &ie_len, pkt_len - WLAN_HDR_A3_LEN - ie_offset);
			if (p != NULL) {
				if (_rtw_memcmp(p+2, WMM_IE, 6)) {

					pstat->flags |= WLAN_STA_WME;
					
					pstat->qos_option = 1;				
					pstat->qos_info = *(p+8);
					
					pstat->max_sp_len = (pstat->qos_info>>5)&0x3;

					if((pstat->qos_info&0xf) !=0xf)
						pstat->has_legacy_ac = _TRUE;
					else
						pstat->has_legacy_ac = _FALSE;
					
					if(pstat->qos_info&0xf)
					{
						if(pstat->qos_info&BIT(0))
							pstat->uapsd_vo = BIT(0)|BIT(1);
						else
							pstat->uapsd_vo = 0;
		
						if(pstat->qos_info&BIT(1))
							pstat->uapsd_vi = BIT(0)|BIT(1);
						else
							pstat->uapsd_vi = 0;
			
						if(pstat->qos_info&BIT(2))
							pstat->uapsd_bk = BIT(0)|BIT(1);
						else
							pstat->uapsd_bk = 0;
			
						if(pstat->qos_info&BIT(3))			
							pstat->uapsd_be = BIT(0)|BIT(1);
						else
							pstat->uapsd_be = 0;
		
					}
	
					break;
				}
			}
			else {
				break;
			}
			p = p + ie_len + 2;
		}
	}


#ifdef CONFIG_80211N_HT
	/* save HT capabilities in the sta object */
	_rtw_memset(&pstat->htpriv.ht_cap, 0, sizeof(struct rtw_ieee80211_ht_cap));
	if (elems.ht_capabilities && elems.ht_capabilities_len >= sizeof(struct rtw_ieee80211_ht_cap)) 
	{
		pstat->flags |= WLAN_STA_HT;
		
		pstat->flags |= WLAN_STA_WME;
		
		_rtw_memcpy(&pstat->htpriv.ht_cap, elems.ht_capabilities, sizeof(struct rtw_ieee80211_ht_cap));			
		
	} else
		pstat->flags &= ~WLAN_STA_HT;

	
	if((pmlmepriv->htpriv.ht_option == _FALSE) && (pstat->flags&WLAN_STA_HT))
	{
		status = _STATS_FAILURE_;
		goto OnAssocReqFail;
	}
		

	if ((pstat->flags & WLAN_STA_HT) &&
		    ((pstat->wpa2_pairwise_cipher&WPA_CIPHER_TKIP) ||
		      (pstat->wpa_pairwise_cipher&WPA_CIPHER_TKIP)))
	{		    
		DBG_871X("HT: " MAC_FMT " tried to "
				   "use TKIP with HT association\n", MAC_ARG(pstat->hwaddr));
		
		//status = WLAN_STATUS_CIPHER_REJECTED_PER_POLICY;
		//goto OnAssocReqFail;
	}
#endif /* CONFIG_80211N_HT */

       //
       //if (hapd->iface->current_mode->mode == HOSTAPD_MODE_IEEE80211G)//?
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

#ifdef CONFIG_P2P
	pstat->is_p2p_device = _FALSE;
	if(rtw_p2p_chk_role(pwdinfo, P2P_ROLE_GO))
	{		
		if( (p2pie=rtw_get_p2p_ie(pframe + WLAN_HDR_A3_LEN + ie_offset , pkt_len - WLAN_HDR_A3_LEN - ie_offset , NULL, &p2pielen)))
		{
			pstat->is_p2p_device = _TRUE;
			if((p2p_status_code=(u8)process_assoc_req_p2p_ie(pwdinfo, pframe, pkt_len, pstat))>0)
			{
				pstat->p2p_status_code = p2p_status_code;
				status = _STATS_CAP_FAIL_;
				goto OnAssocReqFail;
			}
		}
#ifdef CONFIG_WFD
		if(rtw_get_wfd_ie(pframe + WLAN_HDR_A3_LEN + ie_offset , pkt_len - WLAN_HDR_A3_LEN - ie_offset , wfd_ie, &wfd_ielen ))
		{
			u8	attr_content[ 10 ] = { 0x00 };
			u32	attr_contentlen = 0;

			DBG_8192C( "[%s] WFD IE Found!!\n", __FUNCTION__ );
			rtw_get_wfd_attr_content( wfd_ie, wfd_ielen, WFD_ATTR_DEVICE_INFO, attr_content, &attr_contentlen);
			if ( attr_contentlen )
			{
				pwdinfo->wfd_info->peer_rtsp_ctrlport = RTW_GET_BE16( attr_content + 2 );
				DBG_8192C( "[%s] Peer PORT NUM = %d\n", __FUNCTION__, pwdinfo->wfd_info->peer_rtsp_ctrlport );
			}
		}
#endif
	}
	pstat->p2p_status_code = p2p_status_code;
#endif //CONFIG_P2P

	//TODO: identify_proprietary_vendor_ie();
	// Realtek proprietary IE
	// identify if this is Broadcom sta
	// identify if this is ralink sta
	// Customer proprietary IE

	

	/* get a unique AID */
	if (pstat->aid > 0) {
		DBG_871X("  old AID %d\n", pstat->aid);
	} else {
		for (pstat->aid = 1; pstat->aid <= NUM_STA; pstat->aid++)
			if (pstapriv->sta_aid[pstat->aid - 1] == NULL)
				break;
				
		//if (pstat->aid > NUM_STA) {
		if (pstat->aid > pstapriv->max_num_sta) {
				
			pstat->aid = 0;
				
			DBG_871X("  no room for more AIDs\n");

			status = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;
				
			goto OnAssocReqFail;
				
			
		} else {
			pstapriv->sta_aid[pstat->aid - 1] = pstat;
			DBG_871X("allocate new AID = (%d)\n", pstat->aid);
		}	
	}


	pstat->state &= (~WIFI_FW_ASSOC_STATE);	
	pstat->state |= WIFI_FW_ASSOC_SUCCESS;
	
	_enter_critical_bh(&pstapriv->auth_list_lock, &irqL);
	if (!rtw_is_list_empty(&pstat->auth_list))
	{
		rtw_list_delete(&pstat->auth_list);
		pstapriv->auth_list_cnt--;
	}
	_exit_critical_bh(&pstapriv->auth_list_lock, &irqL);

	_enter_critical_bh(&pstapriv->asoc_list_lock, &irqL);	
	if (rtw_is_list_empty(&pstat->asoc_list))
	{
		pstat->expire_to = pstapriv->expire_to;
		rtw_list_insert_tail(&pstat->asoc_list, &pstapriv->asoc_list);
		pstapriv->asoc_list_cnt++;
	}
	_exit_critical_bh(&pstapriv->asoc_list_lock, &irqL);

	// now the station is qualified to join our BSS...	
	if(pstat && (pstat->state & WIFI_FW_ASSOC_SUCCESS) && (_STATS_SUCCESSFUL_==status))
	{
#ifdef CONFIG_NATIVEAP_MLME
		//.1 bss_cap_update & sta_info_update
		bss_cap_update_on_sta_join(padapter, pstat);
		sta_info_update(padapter, pstat);

		//issue assoc rsp before notify station join event.
		if (frame_type == WIFI_ASSOCREQ)
			issue_asocrsp(padapter, status, pstat, WIFI_ASSOCRSP);
		else
			issue_asocrsp(padapter, status, pstat, WIFI_REASSOCRSP);

		//.2 - report to upper layer 
		DBG_871X("indicate_sta_join_event to upper layer - hostapd\n");

#ifdef CONFIG_IOCTL_CFG80211
		#ifdef COMPAT_KERNEL_RELEASE
		rtw_cfg80211_indicate_sta_assoc(padapter, pframe, pkt_len);
		#elif (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37)) && !defined(CONFIG_CFG80211_FORCE_COMPATIBLE_2_6_37_UNDER)
		rtw_cfg80211_indicate_sta_assoc(padapter, pframe, pkt_len);
		#else //(LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37)) && !defined(CONFIG_CFG80211_FORCE_COMPATIBLE_2_6_37_UNDER)
		_enter_critical_bh(&pstat->lock, &irqL);
		if(pstat->passoc_req)
		{
			rtw_mfree(pstat->passoc_req, pstat->assoc_req_len);
			pstat->passoc_req = NULL;
			pstat->assoc_req_len = 0;
		}

		pstat->passoc_req =  rtw_zmalloc(pkt_len);
		if(pstat->passoc_req)
		{
			_rtw_memcpy(pstat->passoc_req, pframe, pkt_len);
			pstat->assoc_req_len = pkt_len;
		}
		_exit_critical_bh(&pstat->lock, &irqL);		
		#endif //(LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37)) && !defined(CONFIG_CFG80211_FORCE_COMPATIBLE_2_6_37_UNDER)
#else
		rtw_indicate_sta_assoc_event(padapter, pstat);
#endif //CONFIG_IOCTL_CFG80211

		//.3-(1) report sta add event
		report_add_sta_event(padapter, pstat->hwaddr, pstat->aid);
		
/*		
		//issue assoc rsp before notify station join event.
		if (frame_type == WIFI_ASSOCREQ)
			issue_asocrsp(padapter, status, pstat, WIFI_ASSOCRSP);
		else
			issue_asocrsp(padapter, status, pstat, WIFI_REASSOCRSP);
*/			
	
#endif
	}

	return _SUCCESS;

asoc_class2_error:

#ifdef CONFIG_NATIVEAP_MLME
	issue_deauth(padapter, (void *)GetAddr2Ptr(pframe), status);
#endif

	return _FAIL;		

OnAssocReqFail:


#ifdef CONFIG_NATIVEAP_MLME
	pstat->aid = 0;
	if (frame_type == WIFI_ASSOCREQ)
		issue_asocrsp(padapter, status, pstat, WIFI_ASSOCRSP);
	else
		issue_asocrsp(padapter, status, pstat, WIFI_REASSOCRSP);
#endif


#endif /* CONFIG_AP_MODE */

	return _FAIL;		

}