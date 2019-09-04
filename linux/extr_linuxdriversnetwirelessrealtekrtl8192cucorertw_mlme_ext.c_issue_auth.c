#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
struct xmit_priv {int dummy; } ;
struct pkt_attrib {int pktlen; int iv_len; int hdrlen; int icv_len; int last_txcmdsz; int /*<<< orphan*/  encrypt; } ;
struct xmit_frame {scalar_t__ buf_addr; struct pkt_attrib attrib; } ;
struct sta_info {int dummy; } ;
struct rtw_ieee80211_hdr_3addr {int dummy; } ;
struct rtw_ieee80211_hdr {unsigned short frame_ctl; int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; } ;
struct mlme_ext_info {scalar_t__ auth_algo; int auth_seq; int state; int key_index; int /*<<< orphan*/  chg_txt; int /*<<< orphan*/  iv; int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {int /*<<< orphan*/  mgnt_seq; struct mlme_ext_info mlmext_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  eeprompriv; struct mlme_ext_priv mlmeextpriv; struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SetFrameSubType (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPrivacy (unsigned short*) ; 
 int /*<<< orphan*/  SetSeqNum (struct rtw_ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int TXDESC_OFFSET ; 
 int /*<<< orphan*/  WIFI_AUTH ; 
 int WIFI_FW_AUTH_STATE ; 
 int WLANHDR_OFFSET ; 
 int _AUTH_ALGM_NUM_ ; 
 int _AUTH_SEQ_NUM_ ; 
 int /*<<< orphan*/  _CHLGETXT_IE_ ; 
 int _STATUS_CODE_ ; 
 int /*<<< orphan*/  _WEP40_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtw_memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct xmit_frame* alloc_mgtxmitframe (struct xmit_priv*) ; 
 unsigned short cpu_to_le16 (unsigned short) ; 
 unsigned int cpu_to_le32 (unsigned int) ; 
 scalar_t__ dot11AuthAlgrthm_Shared ; 
 int /*<<< orphan*/  dump_mgntframe (TYPE_1__*,struct xmit_frame*) ; 
 int /*<<< orphan*/  get_my_bssid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myid (int /*<<< orphan*/ *) ; 
 unsigned char* rtw_set_fixed_ie (unsigned char*,int,unsigned char*,int*) ; 
 unsigned char* rtw_set_ie (unsigned char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtw_wep_encrypt (TYPE_1__*,unsigned char*) ; 
 int /*<<< orphan*/  update_mgntframe_attrib (TYPE_1__*,struct pkt_attrib*) ; 

void issue_auth(_adapter *padapter, struct sta_info *psta, unsigned short status)
{
	struct xmit_frame			*pmgntframe;
	struct pkt_attrib			*pattrib;
	unsigned char					*pframe;
	struct rtw_ieee80211_hdr	*pwlanhdr;
	unsigned short				*fctrl;
	unsigned int					val32;
	unsigned short				val16;
	int use_shared_key = 0;
	struct xmit_priv			*pxmitpriv = &(padapter->xmitpriv);
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

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

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_AUTH);

	pframe += sizeof(struct rtw_ieee80211_hdr_3addr);
	pattrib->pktlen = sizeof(struct rtw_ieee80211_hdr_3addr);


	if(psta)// for AP mode
	{
#ifdef CONFIG_NATIVEAP_MLME

		_rtw_memcpy(pwlanhdr->addr1, psta->hwaddr, ETH_ALEN);		
		_rtw_memcpy(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
		_rtw_memcpy(pwlanhdr->addr3, myid(&(padapter->eeprompriv)), ETH_ALEN);

	
		// setting auth algo number	
		val16 = (u16)psta->authalg;

		if(status != _STATS_SUCCESSFUL_)
			val16 = 0;

		if (val16)	{
			val16 = cpu_to_le16(val16);	
			use_shared_key = 1;
		}

		pframe = rtw_set_fixed_ie(pframe, _AUTH_ALGM_NUM_, (unsigned char *)&val16, &(pattrib->pktlen));

		// setting auth seq number
		val16 =(u16)psta->auth_seq;
		val16 = cpu_to_le16(val16);	
		pframe = rtw_set_fixed_ie(pframe, _AUTH_SEQ_NUM_, (unsigned char *)&val16, &(pattrib->pktlen));

		// setting status code...
		val16 = status;
		val16 = cpu_to_le16(val16);	
		pframe = rtw_set_fixed_ie(pframe, _STATUS_CODE_, (unsigned char *)&val16, &(pattrib->pktlen));

		// added challenging text...
		if ((psta->auth_seq == 2) && (psta->state & WIFI_FW_AUTH_STATE) && (use_shared_key==1))
		{
			pframe = rtw_set_ie(pframe, _CHLGETXT_IE_, 128, psta->chg_txt, &(pattrib->pktlen));			
		}
#endif
	}
	else
	{		
		_rtw_memcpy(pwlanhdr->addr1, get_my_bssid(&pmlmeinfo->network), ETH_ALEN);
		_rtw_memcpy(pwlanhdr->addr2, myid(&padapter->eeprompriv), ETH_ALEN);
		_rtw_memcpy(pwlanhdr->addr3, get_my_bssid(&pmlmeinfo->network), ETH_ALEN);
	
		// setting auth algo number		
		val16 = (pmlmeinfo->auth_algo == dot11AuthAlgrthm_Shared)? 1: 0;// 0:OPEN System, 1:Shared key
		if (val16)	{
			val16 = cpu_to_le16(val16);	
			use_shared_key = 1;
		}	
		//DBG_871X("%s auth_algo= %s auth_seq=%d\n",__FUNCTION__,(pmlmeinfo->auth_algo==0)?"OPEN":"SHARED",pmlmeinfo->auth_seq);
		
		//setting IV for auth seq #3
		if ((pmlmeinfo->auth_seq == 3) && (pmlmeinfo->state & WIFI_FW_AUTH_STATE) && (use_shared_key==1))
		{
			//DBG_871X("==> iv(%d),key_index(%d)\n",pmlmeinfo->iv,pmlmeinfo->key_index);
			val32 = ((pmlmeinfo->iv++) | (pmlmeinfo->key_index << 30));
			val32 = cpu_to_le32(val32);
			pframe = rtw_set_fixed_ie(pframe, 4, (unsigned char *)&val32, &(pattrib->pktlen));

			pattrib->iv_len = 4;
		}

		pframe = rtw_set_fixed_ie(pframe, _AUTH_ALGM_NUM_, (unsigned char *)&val16, &(pattrib->pktlen));
		
		// setting auth seq number
		val16 = pmlmeinfo->auth_seq;
		val16 = cpu_to_le16(val16);	
		pframe = rtw_set_fixed_ie(pframe, _AUTH_SEQ_NUM_, (unsigned char *)&val16, &(pattrib->pktlen));

		
		// setting status code...
		val16 = status;
		val16 = cpu_to_le16(val16);	
		pframe = rtw_set_fixed_ie(pframe, _STATUS_CODE_, (unsigned char *)&val16, &(pattrib->pktlen));

		// then checking to see if sending challenging text...
		if ((pmlmeinfo->auth_seq == 3) && (pmlmeinfo->state & WIFI_FW_AUTH_STATE) && (use_shared_key==1))
		{
			pframe = rtw_set_ie(pframe, _CHLGETXT_IE_, 128, pmlmeinfo->chg_txt, &(pattrib->pktlen));

			SetPrivacy(fctrl);
			
			pattrib->hdrlen = sizeof(struct rtw_ieee80211_hdr_3addr);			
			
			pattrib->encrypt = _WEP40_;

			pattrib->icv_len = 4;
			
			pattrib->pktlen += pattrib->icv_len;			
			
		}
		
	}

	pattrib->last_txcmdsz = pattrib->pktlen;

	rtw_wep_encrypt(padapter, (u8 *)pmgntframe);

	dump_mgntframe(padapter, pmgntframe);

	return;
}