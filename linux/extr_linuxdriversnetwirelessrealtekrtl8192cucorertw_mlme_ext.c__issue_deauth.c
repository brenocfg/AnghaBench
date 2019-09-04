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
struct pkt_attrib {int pktlen; int last_txcmdsz; int /*<<< orphan*/  retry_ctrl; } ;
struct xmit_frame {scalar_t__ buf_addr; struct pkt_attrib attrib; } ;
struct rtw_ieee80211_hdr_3addr {int dummy; } ;
struct rtw_ieee80211_hdr {unsigned short frame_ctl; int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; } ;
struct mlme_ext_info {int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {int /*<<< orphan*/  mgnt_seq; struct mlme_ext_info mlmext_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  eeprompriv; struct mlme_ext_priv mlmeextpriv; struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SetFrameSubType (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSeqNum (struct rtw_ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int TXDESC_OFFSET ; 
 int /*<<< orphan*/  WIFI_DEAUTH ; 
 int WLANHDR_OFFSET ; 
 int _FAIL ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _RSON_CODE_ ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtw_memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct xmit_frame* alloc_mgtxmitframe (struct xmit_priv*) ; 
 unsigned short cpu_to_le16 (unsigned short) ; 
 int /*<<< orphan*/  dump_mgntframe (TYPE_1__*,struct xmit_frame*) ; 
 int dump_mgntframe_and_wait_ack (TYPE_1__*,struct xmit_frame*) ; 
 unsigned char* get_my_bssid (int /*<<< orphan*/ *) ; 
 unsigned char* myid (int /*<<< orphan*/ *) ; 
 unsigned char* rtw_set_fixed_ie (unsigned char*,int /*<<< orphan*/ ,unsigned char*,int*) ; 
 int /*<<< orphan*/  update_mgntframe_attrib (TYPE_1__*,struct pkt_attrib*) ; 

__attribute__((used)) static int _issue_deauth(_adapter *padapter, unsigned char *da, unsigned short reason, u8 wait_ack)
{
	struct xmit_frame			*pmgntframe;
	struct pkt_attrib			*pattrib;
	unsigned char					*pframe;
	struct rtw_ieee80211_hdr	*pwlanhdr;
	unsigned short				*fctrl;
	struct xmit_priv			*pxmitpriv = &(padapter->xmitpriv);
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	int ret = _FAIL;
#ifdef CONFIG_P2P
	struct wifidirect_info *pwdinfo= &(padapter->wdinfo);
#endif //CONFIG_P2P
	
	//DBG_871X("%s to "MAC_FMT"\n", __func__, MAC_ARG(da));

#ifdef CONFIG_P2P
	if ( !( rtw_p2p_chk_state( pwdinfo, P2P_STATE_NONE ) ) && ( pwdinfo->rx_invitereq_info.scan_op_ch_only ) )
	{
		_cancel_timer_ex( &pwdinfo->reset_ch_sitesurvey );
		_set_timer( &pwdinfo->reset_ch_sitesurvey, 10 );
	}
#endif //CONFIG_P2P

	if ((pmgntframe = alloc_mgtxmitframe(pxmitpriv)) == NULL)
	{
		goto exit;
	}

	//update attribute
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);
	pattrib->retry_ctrl = _FALSE;

	_rtw_memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_ctl);
	*(fctrl) = 0;

	_rtw_memcpy(pwlanhdr->addr1, da, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_DEAUTH);

	pframe += sizeof(struct rtw_ieee80211_hdr_3addr);
	pattrib->pktlen = sizeof(struct rtw_ieee80211_hdr_3addr);

	reason = cpu_to_le16(reason);
	pframe = rtw_set_fixed_ie(pframe, _RSON_CODE_ , (unsigned char *)&reason, &(pattrib->pktlen));

	pattrib->last_txcmdsz = pattrib->pktlen;


	if(wait_ack)
	{
		ret = dump_mgntframe_and_wait_ack(padapter, pmgntframe);
	}
	else
	{
		dump_mgntframe(padapter, pmgntframe);
		ret = _SUCCESS;
	}

exit:
	return ret;
}