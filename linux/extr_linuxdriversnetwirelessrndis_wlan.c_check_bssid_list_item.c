#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ndis_80211_bssid_ex {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool check_bssid_list_item(struct ndis_80211_bssid_ex *bssid,
				  int bssid_len, void *buf, int len)
{
	void *buf_end, *bssid_end;

	if (!bssid || bssid_len <= 0 || bssid_len > len)
		return false;

	buf_end = (char *)buf + len;
	bssid_end = (char *)bssid + bssid_len;

	return (int)(buf_end - bssid_end) >= 0 && (int)(bssid_end - buf) >= 0;
}