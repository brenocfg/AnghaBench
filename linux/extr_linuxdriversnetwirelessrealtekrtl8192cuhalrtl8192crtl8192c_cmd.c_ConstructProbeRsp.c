#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct rtw_ieee80211_hdr_3addr {int dummy; } ;
struct rtw_ieee80211_hdr {int /*<<< orphan*/ * addr3; int /*<<< orphan*/ * addr2; int /*<<< orphan*/ * addr1; scalar_t__ frame_ctl; } ;
struct TYPE_5__ {scalar_t__ IELength; int /*<<< orphan*/ * IEs; int /*<<< orphan*/ * MacAddress; } ;
struct mlme_ext_info {TYPE_2__ network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  eeprompriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  TYPE_2__ WLAN_BSSID_EX ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 scalar_t__ MAX_IE_SZ ; 
 int /*<<< orphan*/  SetFrameSubType (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSeqNum (struct rtw_ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_PROBERSP ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * myid (int /*<<< orphan*/ *) ; 

void ConstructProbeRsp(_adapter *padapter, u8 *pframe, u32 *pLength, u8 *StaAddr, BOOLEAN bHideSSID)
{
	struct rtw_ieee80211_hdr	*pwlanhdr;
	u16					*fctrl;	
	u8					*mac, *bssid;
	u32					pktlen;
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	WLAN_BSSID_EX 		*cur_network = &(pmlmeinfo->network);
	
	
	//DBG_871X("%s\n", __FUNCTION__);
	
	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;	
	
	mac = myid(&(padapter->eeprompriv));
	bssid = cur_network->MacAddress;
	
	fctrl = &(pwlanhdr->frame_ctl);
	*(fctrl) = 0;
	_rtw_memcpy(pwlanhdr->addr1, StaAddr, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr2, mac, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr3, bssid, ETH_ALEN);

	SetSeqNum(pwlanhdr, 0);
	SetFrameSubType(fctrl, WIFI_PROBERSP);
	
	pktlen = sizeof(struct rtw_ieee80211_hdr_3addr);
	pframe += pktlen;

	if(cur_network->IELength>MAX_IE_SZ)
		return;

	_rtw_memcpy(pframe, cur_network->IEs, cur_network->IELength);
	pframe += cur_network->IELength;
	pktlen += cur_network->IELength;
	
	*pLength = pktlen;
}