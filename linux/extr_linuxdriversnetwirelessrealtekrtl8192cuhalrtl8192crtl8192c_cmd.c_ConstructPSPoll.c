#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct rtw_ieee80211_hdr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; scalar_t__ frame_ctl; } ;
struct mlme_ext_info {int aid; int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  eeprompriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SetDuration (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetFrameSubType (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPwrMgt (scalar_t__*) ; 
 int /*<<< orphan*/  WIFI_PSPOLL ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_my_bssid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myid (int /*<<< orphan*/ *) ; 

void ConstructPSPoll(_adapter *padapter, u8 *pframe, u32 *pLength)
{
	struct rtw_ieee80211_hdr	*pwlanhdr;
	u16					*fctrl;
	u32					pktlen;
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	//DBG_871X("%s\n", __FUNCTION__);

	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;

	// Frame control.
	fctrl = &(pwlanhdr->frame_ctl);
	*(fctrl) = 0;
	SetPwrMgt(fctrl);
	SetFrameSubType(pframe, WIFI_PSPOLL);

	// AID.
	SetDuration(pframe, (pmlmeinfo->aid | 0xc000));

	// BSSID.
	_rtw_memcpy(pwlanhdr->addr1, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	// TA.
	_rtw_memcpy(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);

	*pLength = 16;
}