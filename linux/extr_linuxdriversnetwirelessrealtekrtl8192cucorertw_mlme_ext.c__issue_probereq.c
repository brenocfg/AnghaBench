#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct xmit_priv {int dummy; } ;
struct pkt_attrib {int pktlen; int last_txcmdsz; } ;
struct xmit_frame {scalar_t__ buf_addr; struct pkt_attrib attrib; } ;
struct rtw_ieee80211_hdr_3addr {int dummy; } ;
struct rtw_ieee80211_hdr {unsigned short frame_ctl; unsigned char* addr1; unsigned char* addr3; unsigned char* addr2; } ;
struct mlme_priv {scalar_t__ wps_probe_req_ie_len; unsigned char* wps_probe_req_ie; } ;
struct mlme_ext_info {int dummy; } ;
struct mlme_ext_priv {int /*<<< orphan*/  mgnt_seq; struct mlme_ext_info mlmext_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  eeprompriv; struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_10__ {int SsidLength; unsigned char* Ssid; } ;
typedef  TYPE_2__ NDIS_802_11_SSID ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int NumRates ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SetFrameSubType (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSeqNum (struct rtw_ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int TXDESC_OFFSET ; 
 int /*<<< orphan*/  WIFI_PROBEREQ ; 
 int WLANHDR_OFFSET ; 
 int /*<<< orphan*/  _EXT_SUPPORTEDRATES_IE_ ; 
 int _FAIL ; 
 int /*<<< orphan*/  _SSID_IE_ ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _SUPPORTEDRATES_IE_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/  _rtw_memcpy (unsigned char*,...) ; 
 int /*<<< orphan*/  _rtw_memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct xmit_frame* alloc_mgtxmitframe (struct xmit_priv*) ; 
 int /*<<< orphan*/  dump_mgntframe (TYPE_1__*,struct xmit_frame*) ; 
 int dump_mgntframe_and_wait_ack (TYPE_1__*,struct xmit_frame*) ; 
 int /*<<< orphan*/  get_rate_set (TYPE_1__*,unsigned char*,int*) ; 
 unsigned char* myid (int /*<<< orphan*/ *) ; 
 unsigned char* rtw_set_ie (unsigned char*,int /*<<< orphan*/ ,int,unsigned char*,int*) ; 
 int /*<<< orphan*/  update_mgntframe_attrib (TYPE_1__*,struct pkt_attrib*) ; 

int _issue_probereq(_adapter *padapter, NDIS_802_11_SSID *pssid, u8 *da, int wait_ack)
{
	int ret = _FAIL;
	struct xmit_frame		*pmgntframe;
	struct pkt_attrib		*pattrib;
	unsigned char			*pframe;
	struct rtw_ieee80211_hdr	*pwlanhdr;
	unsigned short		*fctrl;
	unsigned char			*mac;
	unsigned char			bssrate[NumRates];
	struct xmit_priv		*pxmitpriv = &(padapter->xmitpriv);
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	int	bssrate_len = 0;
	u8	bc_addr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

	RT_TRACE(_module_rtl871x_mlme_c_,_drv_notice_,("+issue_probereq\n"));

	if ((pmgntframe = alloc_mgtxmitframe(pxmitpriv)) == NULL)
	{
		goto exit;
	}

	//update attribute
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);


	_rtw_memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;

	mac = myid(&(padapter->eeprompriv));

	fctrl = &(pwlanhdr->frame_ctl);
	*(fctrl) = 0;

	if (da)
	{
		//	unicast probe request frame
		_rtw_memcpy(pwlanhdr->addr1, da, ETH_ALEN);
		_rtw_memcpy(pwlanhdr->addr3, da, ETH_ALEN);
	}
	else
	{
		//	broadcast probe request frame
		_rtw_memcpy(pwlanhdr->addr1, bc_addr, ETH_ALEN);
		_rtw_memcpy(pwlanhdr->addr3, bc_addr, ETH_ALEN);
	}

	_rtw_memcpy(pwlanhdr->addr2, mac, ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_PROBEREQ);

	pframe += sizeof (struct rtw_ieee80211_hdr_3addr);
	pattrib->pktlen = sizeof (struct rtw_ieee80211_hdr_3addr);

	if(pssid)
		pframe = rtw_set_ie(pframe, _SSID_IE_, pssid->SsidLength, pssid->Ssid, &(pattrib->pktlen));
	else
		pframe = rtw_set_ie(pframe, _SSID_IE_, 0, NULL, &(pattrib->pktlen));

	get_rate_set(padapter, bssrate, &bssrate_len);

	if (bssrate_len > 8)
	{
		pframe = rtw_set_ie(pframe, _SUPPORTEDRATES_IE_ , 8, bssrate, &(pattrib->pktlen));
		pframe = rtw_set_ie(pframe, _EXT_SUPPORTEDRATES_IE_ , (bssrate_len - 8), (bssrate + 8), &(pattrib->pktlen));
	}
	else
	{
		pframe = rtw_set_ie(pframe, _SUPPORTEDRATES_IE_ , bssrate_len , bssrate, &(pattrib->pktlen));
	}

#if 0
	//add wps_ie for wps2.0
	if(pmlmepriv->probereq_wpsie_len>0 && pmlmepriv->probereq_wpsie_len<MAX_WPS_IE_LEN)
	{
		_rtw_memcpy(pframe, pmlmepriv->probereq_wpsie, pmlmepriv->probereq_wpsie_len);
		pframe += pmlmepriv->probereq_wpsie_len;
		pattrib->pktlen += pmlmepriv->probereq_wpsie_len;
		//pmlmepriv->probereq_wpsie_len = 0 ;//reset to zero		
	}	
#else
	//add wps_ie for wps2.0
	if(pmlmepriv->wps_probe_req_ie_len>0 && pmlmepriv->wps_probe_req_ie)
	{
		_rtw_memcpy(pframe, pmlmepriv->wps_probe_req_ie, pmlmepriv->wps_probe_req_ie_len);
		pframe += pmlmepriv->wps_probe_req_ie_len;
		pattrib->pktlen += pmlmepriv->wps_probe_req_ie_len;
		//pmlmepriv->wps_probe_req_ie_len = 0 ;//reset to zero		
	}	
#endif

	pattrib->last_txcmdsz = pattrib->pktlen;

	RT_TRACE(_module_rtl871x_mlme_c_,_drv_notice_,("issuing probe_req, tx_len=%d\n", pattrib->last_txcmdsz));

	if (wait_ack) {
		ret = dump_mgntframe_and_wait_ack(padapter, pmgntframe);
	} else {
		dump_mgntframe(padapter, pmgntframe);
		ret = _SUCCESS;
	}

exit:
	return ret;
}