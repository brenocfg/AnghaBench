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
struct TYPE_4__ {int InfrastructureMode; } ;
struct wlan_network {TYPE_1__ network; } ;
struct rtw_ieee80211_hdr_3addr {int dummy; } ;
struct rtw_ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; scalar_t__ frame_ctl; } ;
struct mlme_priv {struct wlan_network cur_network; } ;
struct mlme_ext_info {int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  eeprompriv; struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
#define  Ndis802_11APMode 130 
#define  Ndis802_11IBSS 129 
#define  Ndis802_11Infrastructure 128 
 int /*<<< orphan*/  SetFrDs (scalar_t__*) ; 
 int /*<<< orphan*/  SetFrameSubType (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPwrMgt (scalar_t__*) ; 
 int /*<<< orphan*/  SetSeqNum (struct rtw_ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetToDs (scalar_t__*) ; 
 int /*<<< orphan*/  WIFI_DATA_NULL ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_my_bssid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * myid (int /*<<< orphan*/ *) ; 

void ConstructNullFunctionData(_adapter *padapter, u8 *pframe, u32 *pLength, u8 *StaAddr, BOOLEAN bForcePowerSave)
{
	struct rtw_ieee80211_hdr	*pwlanhdr;
	u16					*fctrl;
	u32					pktlen;
	struct mlme_priv		*pmlmepriv = &padapter->mlmepriv;
	struct wlan_network	*cur_network = &pmlmepriv->cur_network;
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	//DBG_871X("%s:%d\n", __FUNCTION__, bForcePowerSave);

	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_ctl);
	*(fctrl) = 0;
	if (bForcePowerSave)
	{
		SetPwrMgt(fctrl);
	}

	switch(cur_network->network.InfrastructureMode)
	{			
		case Ndis802_11Infrastructure:
			SetToDs(fctrl);
			_rtw_memcpy(pwlanhdr->addr1, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);
			_rtw_memcpy(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
			_rtw_memcpy(pwlanhdr->addr3, StaAddr, ETH_ALEN);
			break;
		case Ndis802_11APMode:
			SetFrDs(fctrl);
			_rtw_memcpy(pwlanhdr->addr1, StaAddr, ETH_ALEN);
			_rtw_memcpy(pwlanhdr->addr2, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);
			_rtw_memcpy(pwlanhdr->addr3, myid(&(padapter->eeprompriv)), ETH_ALEN);
			break;
		case Ndis802_11IBSS:
		default:
			_rtw_memcpy(pwlanhdr->addr1, StaAddr, ETH_ALEN);
			_rtw_memcpy(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
			_rtw_memcpy(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);
			break;
	}

	SetSeqNum(pwlanhdr, 0);

	SetFrameSubType(pframe, WIFI_DATA_NULL);

	pframe += sizeof(struct rtw_ieee80211_hdr_3addr);
	pktlen = sizeof(struct rtw_ieee80211_hdr_3addr);

	*pLength = pktlen;
}