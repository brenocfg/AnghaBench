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

unsigned int OnAuth(_adapter *padapter, union recv_frame *precv_frame)
{
#ifdef CONFIG_AP_MODE
	_irqL irqL;
	unsigned int	auth_mode, seq, ie_len;	
	unsigned char	*sa, *p;	
	u16	algorithm;
	int	status;
	static struct sta_info stat;	
	struct	sta_info	*pstat=NULL;	
	struct	sta_priv *pstapriv = &padapter->stapriv;
	struct security_priv *psecuritypriv = &padapter->securitypriv;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 *pframe = precv_frame->u.hdr.rx_data; 
	uint len = precv_frame->u.hdr.len;

	
#ifdef CONFIG_CONCURRENT_MODE	
	if(((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE) &&
		check_buddy_fwstate(padapter, _FW_UNDER_LINKING|_FW_UNDER_SURVEY))
	{
		//don't process auth request;
		return _SUCCESS;
	}
#endif //CONFIG_CONCURRENT_MODE

	if((pmlmeinfo->state&0x03) != WIFI_FW_AP_STATE)
		return _FAIL;

	DBG_871X("+OnAuth\n");
	
	sa = GetAddr2Ptr(pframe);
	
	auth_mode = psecuritypriv->dot11AuthAlgrthm;
	seq = cpu_to_le16(*(u16*)((SIZE_PTR)pframe + WLAN_HDR_A3_LEN + 2));
	algorithm = cpu_to_le16(*(u16*)((SIZE_PTR)pframe + WLAN_HDR_A3_LEN));

	if (GetPrivacy(pframe))
	{	
#if 0 //TODO: SW rtw_wep_decrypt
		if (SWCRYPTO)
		{
			status = rtw_wep_decrypt(priv, pframe, pfrinfo->pktlen,
				priv->pmib->dot1180211AuthEntry.dot11PrivacyAlgrthm);
			if (status == FALSE)
			{
				SAVE_INT_AND_CLI(flags);
				RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,"wep-decrypt a Auth frame error!\n");
				status = _STATS_CHALLENGE_FAIL_;
				goto auth_fail;
			}
		}

		seq = cpu_to_le16(*(unsigned short *)((unsigned int)pframe + WLAN_HDR_A3_LEN + 4 + 2));
		algorithm = cpu_to_le16(*(unsigned short *)((unsigned int)pframe + WLAN_HDR_A3_LEN + 4));
#endif
	}


	DBG_871X("auth alg=%x, seq=%X\n", algorithm, seq);

	if (auth_mode == 2 &&
			psecuritypriv->dot11PrivacyAlgrthm != _WEP40_ &&
			psecuritypriv->dot11PrivacyAlgrthm != _WEP104_)
		auth_mode = 0;

	if ((algorithm > 0 && auth_mode == 0) ||	// rx a shared-key auth but shared not enabled
		(algorithm == 0 && auth_mode == 1) )	// rx a open-system auth but shared-key is enabled
	{		
		DBG_871X("auth rejected due to bad alg [alg=%d, auth_mib=%d] %02X%02X%02X%02X%02X%02X\n",
			algorithm, auth_mode, sa[0], sa[1], sa[2], sa[3], sa[4], sa[5]);
		
		status = _STATS_NO_SUPP_ALG_;
		
		goto auth_fail;
	}
	
#if 0 //ACL control	
	phead = &priv->wlan_acl_list;
	plist = phead->next;
	//check sa
	if (acl_mode == 1)		// 1: positive check, only those on acl_list can be connected.
		res = FAIL;
	else
		res = SUCCESS;

	while(plist != phead)
	{
		paclnode = list_entry(plist, struct rtw_wlan_acl_node, list);
		plist = plist->next;
		if (!memcmp((void *)sa, paclnode->addr, 6)) {
			if (paclnode->mode & 2) { // deny
				res = FAIL;
				break;
			}
			else {
				res = SUCCESS;
				break;
			}
		}
	}

	if (res != SUCCESS) {
		RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,"auth abort because ACL!\n");
		return FAIL;
	}
#else
	if(rtw_access_ctrl(padapter, sa) == _FALSE)
	{
		status = _STATS_UNABLE_HANDLE_STA_;
		goto auth_fail;
	}	
#endif

	pstat = rtw_get_stainfo(pstapriv, sa);
	if (pstat == NULL)
	{
		// allocate a new one
		DBG_871X("going to alloc stainfo for sa="MAC_FMT"\n",  MAC_ARG(sa));
		pstat = rtw_alloc_stainfo(pstapriv, sa);
		if (pstat == NULL)
		{
			DBG_871X(" Exceed the upper limit of supported clients...\n");
			status = _STATS_UNABLE_HANDLE_STA_;
			goto auth_fail;
		}
		
		pstat->state = WIFI_FW_AUTH_NULL;
		pstat->auth_seq = 0;
		
		//pstat->flags = 0;
		//pstat->capability = 0;
	}
	else
	{		
		_enter_critical_bh(&pstapriv->asoc_list_lock, &irqL);
		if(rtw_is_list_empty(&pstat->asoc_list)==_FALSE)
		{			
			rtw_list_delete(&pstat->asoc_list);
			pstapriv->asoc_list_cnt--;
			if (pstat->expire_to > 0)
			{
				//TODO: STA re_auth within expire_to
			}
		}
		_exit_critical_bh(&pstapriv->asoc_list_lock, &irqL);
		
		if (seq==1) {
			//TODO: STA re_auth and auth timeout 
		}
	}

	_enter_critical_bh(&pstapriv->auth_list_lock, &irqL);
	if (rtw_is_list_empty(&pstat->auth_list))
	{		
		rtw_list_insert_tail(&pstat->auth_list, &pstapriv->auth_list);
		pstapriv->auth_list_cnt++;
	}	
	_exit_critical_bh(&pstapriv->auth_list_lock, &irqL);

	if (pstat->auth_seq == 0)
		pstat->expire_to = pstapriv->auth_to;

	if ((pstat->auth_seq + 1) != seq)
	{
		DBG_871X("(1)auth rejected because out of seq [rx_seq=%d, exp_seq=%d]!\n",
			seq, pstat->auth_seq+1);
		status = _STATS_OUT_OF_AUTH_SEQ_;
		goto auth_fail;
	}

	if (algorithm==0 && (auth_mode == 0 || auth_mode == 2))
	{
		if (seq == 1)
		{
			pstat->state &= ~WIFI_FW_AUTH_NULL;
			pstat->state |= WIFI_FW_AUTH_SUCCESS;
			pstat->expire_to = pstapriv->assoc_to;
			pstat->authalg = algorithm;
		}
		else
		{
			DBG_871X("(2)auth rejected because out of seq [rx_seq=%d, exp_seq=%d]!\n",
				seq, pstat->auth_seq+1);
			status = _STATS_OUT_OF_AUTH_SEQ_;
			goto auth_fail;
		}
	}
	else // shared system or auto authentication
	{
		if (seq == 1)
		{
			//prepare for the challenging txt...
			
			//get_random_bytes((void *)pstat->chg_txt, 128);//TODO:
			
			pstat->state &= ~WIFI_FW_AUTH_NULL;
			pstat->state |= WIFI_FW_AUTH_STATE;
			pstat->authalg = algorithm;
			pstat->auth_seq = 2;
		}
		else if (seq == 3)
		{
			//checking for challenging txt...
			DBG_871X("checking for challenging txt...\n");
			
			p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + 4 + _AUTH_IE_OFFSET_ , _CHLGETXT_IE_, (int *)&ie_len,
					len - WLAN_HDR_A3_LEN - _AUTH_IE_OFFSET_ - 4);

			if((p==NULL) || (ie_len<=0))
			{
				DBG_871X("auth rejected because challenge failure!(1)\n");
				status = _STATS_CHALLENGE_FAIL_;
				goto auth_fail;
			}
			
			if (_rtw_memcmp((void *)(p + 2), pstat->chg_txt, 128))
			{
				pstat->state &= (~WIFI_FW_AUTH_STATE);
				pstat->state |= WIFI_FW_AUTH_SUCCESS;
				// challenging txt is correct...
				pstat->expire_to =  pstapriv->assoc_to;
			}
			else
			{
				DBG_871X("auth rejected because challenge failure!\n");
				status = _STATS_CHALLENGE_FAIL_;
				goto auth_fail;
			}
		}
		else
		{
			DBG_871X("(3)auth rejected because out of seq [rx_seq=%d, exp_seq=%d]!\n",
				seq, pstat->auth_seq+1);
			status = _STATS_OUT_OF_AUTH_SEQ_;
			goto auth_fail;
		}
	}


	// Now, we are going to issue_auth...
	pstat->auth_seq = seq + 1;	
	
#ifdef CONFIG_NATIVEAP_MLME
	issue_auth(padapter, pstat, (unsigned short)(_STATS_SUCCESSFUL_));
#endif

	if (pstat->state & WIFI_FW_AUTH_SUCCESS)
		pstat->auth_seq = 0;

		
	return _SUCCESS;

auth_fail:

	if(pstat)
		rtw_free_stainfo(padapter , pstat);
	
	pstat = &stat;
	_rtw_memset((char *)pstat, '\0', sizeof(stat));
	pstat->auth_seq = 2;
	_rtw_memcpy(pstat->hwaddr, sa, 6);	
	
#ifdef CONFIG_NATIVEAP_MLME
	issue_auth(padapter, pstat, (unsigned short)status);	
#endif

#endif
	return _FAIL;

}