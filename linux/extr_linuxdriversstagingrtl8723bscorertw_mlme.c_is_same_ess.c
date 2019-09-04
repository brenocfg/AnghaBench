#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ SsidLength; int /*<<< orphan*/  Ssid; } ;
struct wlan_bssid_ex {TYPE_1__ Ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

inline int is_same_ess(struct wlan_bssid_ex *a, struct wlan_bssid_ex *b)
{
	/* RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("(%s,%d)(%s,%d)\n", */
	/* 		a->Ssid.Ssid, a->Ssid.SsidLength, b->Ssid.Ssid, b->Ssid.SsidLength)); */
	return (a->Ssid.SsidLength == b->Ssid.SsidLength)
		&&  !memcmp(a->Ssid.Ssid, b->Ssid.Ssid, a->Ssid.SsidLength);
}