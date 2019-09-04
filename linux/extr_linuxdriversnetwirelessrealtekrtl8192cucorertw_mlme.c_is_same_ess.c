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
struct TYPE_5__ {scalar_t__ SsidLength; int /*<<< orphan*/  Ssid; } ;
struct TYPE_6__ {TYPE_1__ Ssid; } ;
typedef  TYPE_2__ WLAN_BSSID_EX ;

/* Variables and functions */
 scalar_t__ _TRUE ; 
 scalar_t__ _rtw_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

inline int is_same_ess(WLAN_BSSID_EX *a, WLAN_BSSID_EX *b)
{
	//RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("(%s,%d)(%s,%d)\n",
	//		a->Ssid.Ssid,a->Ssid.SsidLength,b->Ssid.Ssid,b->Ssid.SsidLength));
	return (a->Ssid.SsidLength == b->Ssid.SsidLength) 
		&&  _rtw_memcmp(a->Ssid.Ssid, b->Ssid.Ssid, a->Ssid.SsidLength)==_TRUE;
}