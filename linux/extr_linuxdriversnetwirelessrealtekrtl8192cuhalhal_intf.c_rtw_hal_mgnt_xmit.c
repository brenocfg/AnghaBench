#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
struct TYPE_6__ {int /*<<< orphan*/  ra; } ;
struct xmit_frame {TYPE_1__ attrib; scalar_t__ buf_addr; } ;
struct rtw_ieee80211_hdr {int /*<<< orphan*/  addr1; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_7__ {int /*<<< orphan*/  (* mgnt_xmit ) (TYPE_3__*,struct xmit_frame*) ;} ;
struct TYPE_8__ {TYPE_2__ HalFunc; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int TXDESC_OFFSET ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct xmit_frame*) ; 

s32	rtw_hal_mgnt_xmit(_adapter *padapter, struct xmit_frame *pmgntframe)
{
	s32 ret = _FAIL;
	unsigned char	*pframe;
	struct rtw_ieee80211_hdr	*pwlanhdr;
	
	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;
	_rtw_memcpy(pmgntframe->attrib.ra, pwlanhdr->addr1, ETH_ALEN);

#ifdef CONFIG_IEEE80211W
	if(padapter->securitypriv.binstallBIPkey == _TRUE)
	{
		if(IS_MCAST(pmgntframe->attrib.ra))
		{
			pmgntframe->attrib.encrypt = _BIP_;
			//pmgntframe->attrib.bswenc = _TRUE;
		}	
		else
		{
			pmgntframe->attrib.encrypt = _AES_;
			pmgntframe->attrib.bswenc = _TRUE;
		}
		rtw_mgmt_xmitframe_coalesce(padapter, pmgntframe->pkt, pmgntframe);
	}
#endif //CONFIG_IEEE80211W
	
	if(padapter->HalFunc.mgnt_xmit)
		ret = padapter->HalFunc.mgnt_xmit(padapter, pmgntframe);
	return ret;
}