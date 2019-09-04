#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_5__ {scalar_t__ SsidLength; int /*<<< orphan*/  Ssid; } ;
struct TYPE_6__ {TYPE_1__ Ssid; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  IEs; } ;
typedef  TYPE_2__ WLAN_BSSID_EX ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int WLAN_CAPABILITY_BSS ; 
 int WLAN_CAPABILITY_IBSS ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 scalar_t__ _rtw_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  rtw_get_capability_from_ie (int /*<<< orphan*/ ) ; 

int is_same_network(WLAN_BSSID_EX *src, WLAN_BSSID_EX *dst)
{
	 u16 s_cap, d_cap;
	 
_func_enter_;	

#ifdef PLATFORM_OS_XP
	 if ( ((uint)dst) <= 0x7fffffff || 
	 	((uint)src) <= 0x7fffffff ||
	 	((uint)&s_cap) <= 0x7fffffff ||
	 	((uint)&d_cap) <= 0x7fffffff)
	{
		RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("\n@@@@ error address of dst\n"));
			
		KeBugCheckEx(0x87110000, (ULONG_PTR)dst, (ULONG_PTR)src,(ULONG_PTR)&s_cap, (ULONG_PTR)&d_cap);

		return _FALSE;
	}
#endif


	_rtw_memcpy((u8 *)&s_cap, rtw_get_capability_from_ie(src->IEs), 2);
	_rtw_memcpy((u8 *)&d_cap, rtw_get_capability_from_ie(dst->IEs), 2);

	
	s_cap = le16_to_cpu(s_cap);
	d_cap = le16_to_cpu(d_cap);
	
_func_exit_;			

	return ((src->Ssid.SsidLength == dst->Ssid.SsidLength) &&
		//	(src->Configuration.DSConfig == dst->Configuration.DSConfig) &&
			( (_rtw_memcmp(src->MacAddress, dst->MacAddress, ETH_ALEN)) == _TRUE) &&
			( (_rtw_memcmp(src->Ssid.Ssid, dst->Ssid.Ssid, src->Ssid.SsidLength)) == _TRUE) &&
			((s_cap & WLAN_CAPABILITY_IBSS) == 
			(d_cap & WLAN_CAPABILITY_IBSS)) &&
			((s_cap & WLAN_CAPABILITY_BSS) == 
			(d_cap & WLAN_CAPABILITY_BSS)));
	
}