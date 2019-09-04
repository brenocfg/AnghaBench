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
struct mlme_ext_info {int state; int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {int /*<<< orphan*/  mgnt_seq; struct mlme_ext_info mlmext_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  eeprompriv; struct mlme_ext_priv mlmeextpriv; struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SetFrDs (unsigned short*) ; 
 int /*<<< orphan*/  SetFrameSubType (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPwrMgt (unsigned short*) ; 
 int /*<<< orphan*/  SetSeqNum (struct rtw_ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetToDs (unsigned short*) ; 
 int TXDESC_OFFSET ; 
 int /*<<< orphan*/  WIFI_DATA_NULL ; 
 int WIFI_FW_AP_STATE ; 
 int WIFI_FW_STATION_STATE ; 
 int WLANHDR_OFFSET ; 
 int _FAIL ; 
 int /*<<< orphan*/  _FALSE ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtw_memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct xmit_frame* alloc_mgtxmitframe (struct xmit_priv*) ; 
 int /*<<< orphan*/  dump_mgntframe (TYPE_1__*,struct xmit_frame*) ; 
 int dump_mgntframe_and_wait_ack (TYPE_1__*,struct xmit_frame*) ; 
 unsigned char* get_my_bssid (int /*<<< orphan*/ *) ; 
 unsigned char* myid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_mgntframe_attrib (TYPE_1__*,struct pkt_attrib*) ; 

__attribute__((used)) static int _issue_nulldata(_adapter *padapter, unsigned char *da, unsigned int power_mode, int wait_ack)
{
	int ret = _FAIL;
	struct xmit_frame			*pmgntframe;
	struct pkt_attrib			*pattrib;
	unsigned char					*pframe;
	struct rtw_ieee80211_hdr	*pwlanhdr;
	unsigned short				*fctrl;
	struct xmit_priv	*pxmitpriv;
	struct mlme_ext_priv	*pmlmeext;
	struct mlme_ext_info	*pmlmeinfo;

	//DBG_871X("%s:%d\n", __FUNCTION__, power_mode);

	if(!padapter)
		goto exit;

	pxmitpriv = &(padapter->xmitpriv);
	pmlmeext = &(padapter->mlmeextpriv);
	pmlmeinfo = &(pmlmeext->mlmext_info);

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

	if((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE)
	{
		SetFrDs(fctrl);
	}
	else if((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE)
	{
		SetToDs(fctrl);
	}
	
	if (power_mode)
	{
		SetPwrMgt(fctrl);
	}

	_rtw_memcpy(pwlanhdr->addr1, da, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_DATA_NULL);

	pframe += sizeof(struct rtw_ieee80211_hdr_3addr);
	pattrib->pktlen = sizeof(struct rtw_ieee80211_hdr_3addr);

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