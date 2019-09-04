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
struct sta_info {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */

void issue_asocrsp(_adapter *padapter, unsigned short status, struct sta_info *pstat, int pkt_type)
{
#ifdef CONFIG_AP_MODE
	struct xmit_frame	*pmgntframe;
	struct rtw_ieee80211_hdr	*pwlanhdr;
	struct pkt_attrib *pattrib;
	unsigned char	*pbuf, *pframe;
	unsigned short val;		
	unsigned short *fctrl;
	struct xmit_priv *pxmitpriv = &(padapter->xmitpriv);
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);	
	WLAN_BSSID_EX *pnetwork = &(pmlmeinfo->network);
	u8 *ie = pnetwork->IEs; 
#ifdef CONFIG_P2P
	struct wifidirect_info	*pwdinfo = &(padapter->wdinfo);
#ifdef CONFIG_WFD
	u32					wfdielen = 0;
#endif //CONFIG_WFD
#endif //CONFIG_P2P

	DBG_871X("%s\n", __FUNCTION__);

	if ((pmgntframe = alloc_mgtxmitframe(pxmitpriv)) == NULL)
	{
		return;
	}

	//update attribute
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);


	_rtw_memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_ctl);
	*(fctrl) = 0;

	_rtw_memcpy((void *)GetAddr1Ptr(pwlanhdr), pstat->hwaddr, ETH_ALEN);
	_rtw_memcpy((void *)GetAddr2Ptr(pwlanhdr), myid(&(padapter->eeprompriv)), ETH_ALEN);
	_rtw_memcpy((void *)GetAddr3Ptr(pwlanhdr), get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);


	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	if ((pkt_type == WIFI_ASSOCRSP) || (pkt_type == WIFI_REASSOCRSP))
		SetFrameSubType(pwlanhdr, pkt_type);		
	else
		return;

	pattrib->hdrlen = sizeof(struct rtw_ieee80211_hdr_3addr);
	pattrib->pktlen += pattrib->hdrlen;
	pframe += pattrib->hdrlen;

	//capability
	val = *(unsigned short *)rtw_get_capability_from_ie(ie);

	pframe = rtw_set_fixed_ie(pframe, _CAPABILITY_ , (unsigned char *)&val, &(pattrib->pktlen));

	status = cpu_to_le16(status);
	pframe = rtw_set_fixed_ie(pframe , _STATUS_CODE_ , (unsigned char *)&status, &(pattrib->pktlen));
	
	val = cpu_to_le16(pstat->aid | BIT(14) | BIT(15));
	pframe = rtw_set_fixed_ie(pframe, _ASOC_ID_ , (unsigned char *)&val, &(pattrib->pktlen));

	if (pstat->bssratelen <= 8)
	{
		pframe = rtw_set_ie(pframe, _SUPPORTEDRATES_IE_, pstat->bssratelen, pstat->bssrateset, &(pattrib->pktlen));
	}	
	else 
	{
		pframe = rtw_set_ie(pframe, _SUPPORTEDRATES_IE_, 8, pstat->bssrateset, &(pattrib->pktlen));
		pframe = rtw_set_ie(pframe, _EXT_SUPPORTEDRATES_IE_, (pstat->bssratelen-8), pstat->bssrateset+8, &(pattrib->pktlen));
	}

#ifdef CONFIG_80211N_HT
	if ((pstat->flags & WLAN_STA_HT) && (pmlmepriv->htpriv.ht_option))
	{
		uint ie_len=0;
		
		//FILL HT CAP INFO IE
		//p = hostapd_eid_ht_capabilities_info(hapd, p);
		pbuf = rtw_get_ie(ie + _BEACON_IE_OFFSET_, _HT_CAPABILITY_IE_, &ie_len, (pnetwork->IELength - _BEACON_IE_OFFSET_));
		if(pbuf && ie_len>0)
		{
			_rtw_memcpy(pframe, pbuf, ie_len+2);
			pframe += (ie_len+2);
			pattrib->pktlen +=(ie_len+2);
		}

		//FILL HT ADD INFO IE
		//p = hostapd_eid_ht_operation(hapd, p);
		pbuf = rtw_get_ie(ie + _BEACON_IE_OFFSET_, _HT_ADD_INFO_IE_, &ie_len, (pnetwork->IELength - _BEACON_IE_OFFSET_));
		if(pbuf && ie_len>0)
		{
			_rtw_memcpy(pframe, pbuf, ie_len+2);
			pframe += (ie_len+2);
			pattrib->pktlen +=(ie_len+2);
		}
		
	}	
#endif

	//FILL WMM IE
	if ((pstat->flags & WLAN_STA_WME) && (pmlmepriv->qospriv.qos_option))
	{
		uint ie_len=0;
		unsigned char WMM_PARA_IE[] = {0x00, 0x50, 0xf2, 0x02, 0x01, 0x01};	
		
		for (pbuf = ie + _BEACON_IE_OFFSET_; ;pbuf+= (ie_len + 2))
		{			
			pbuf = rtw_get_ie(pbuf, _VENDOR_SPECIFIC_IE_, &ie_len, (pnetwork->IELength - _BEACON_IE_OFFSET_ - (ie_len + 2)));	
			if(pbuf && _rtw_memcmp(pbuf+2, WMM_PARA_IE, 6)) 
			{				
				_rtw_memcpy(pframe, pbuf, ie_len+2);
				pframe += (ie_len+2);
				pattrib->pktlen +=(ie_len+2);
				
				break;				
			}
			
			if ((pbuf == NULL) || (ie_len == 0))
			{
				break;
			}			
		}
		
	}


	if (pmlmeinfo->assoc_AP_vendor == realtekAP)
	{
		pframe = rtw_set_ie(pframe, _VENDOR_SPECIFIC_IE_, 6 , REALTEK_96B_IE, &(pattrib->pktlen));
	}

	//add WPS IE ie for wps 2.0
	if(pmlmepriv->wps_assoc_resp_ie && pmlmepriv->wps_assoc_resp_ie_len>0)
	{
		_rtw_memcpy(pframe, pmlmepriv->wps_assoc_resp_ie, pmlmepriv->wps_assoc_resp_ie_len);
		
		pframe += pmlmepriv->wps_assoc_resp_ie_len;
		pattrib->pktlen += pmlmepriv->wps_assoc_resp_ie_len;
	}

#ifdef CONFIG_P2P
	if( padapter->wdinfo.driver_interface == DRIVER_WEXT )
	{
		if(rtw_p2p_chk_role(pwdinfo, P2P_ROLE_GO) && (pstat->is_p2p_device == _TRUE))
		{
			u32 len;

			len = build_assoc_resp_p2p_ie(pwdinfo, pframe, pstat->p2p_status_code);

			pframe += len;
			pattrib->pktlen += len;
		}
	}
#ifdef CONFIG_WFD
	if(rtw_p2p_chk_role(pwdinfo, P2P_ROLE_GO)
#ifdef CONFIG_IOCTL_CFG80211		
		&& (_TRUE == pwdinfo->wfd_info->wfd_enable)
#endif //CONFIG_IOCTL_CFG80211	
	)
	{
		wfdielen = build_assoc_resp_wfd_ie(pwdinfo, pframe);
		pframe += wfdielen;
		pattrib->pktlen += wfdielen;
	}
#endif //CONFIG_WFD
#endif //CONFIG_P2P

	pattrib->last_txcmdsz = pattrib->pktlen;
	
	dump_mgntframe(padapter, pmgntframe);
	
#endif
}