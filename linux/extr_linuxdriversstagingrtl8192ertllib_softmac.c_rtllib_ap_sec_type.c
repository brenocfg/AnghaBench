#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int capability; } ;
struct TYPE_4__ {size_t tx_keyidx; struct lib80211_crypt_data** crypt; } ;
struct rtllib_device {int wpa_ie_len; int* wpa_ie; scalar_t__ host_encrypt; TYPE_2__ current_network; TYPE_1__ crypt_info; } ;
struct lib80211_crypt_data {TYPE_3__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int SEC_ALG_CCMP ; 
 int SEC_ALG_NONE ; 
 int SEC_ALG_TKIP ; 
 int SEC_ALG_WEP ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

u8 rtllib_ap_sec_type(struct rtllib_device *ieee)
{
	static u8 ccmp_ie[4] = {0x00, 0x50, 0xf2, 0x04};
	static u8 ccmp_rsn_ie[4] = {0x00, 0x0f, 0xac, 0x04};
	int wpa_ie_len = ieee->wpa_ie_len;
	struct lib80211_crypt_data *crypt;
	int encrypt;

	crypt = ieee->crypt_info.crypt[ieee->crypt_info.tx_keyidx];
	encrypt = (ieee->current_network.capability & WLAN_CAPABILITY_PRIVACY)
		  || (ieee->host_encrypt && crypt && crypt->ops &&
		  (strcmp(crypt->ops->name, "R-WEP") == 0));

	/* simply judge  */
	if (encrypt && (wpa_ie_len == 0)) {
		return SEC_ALG_WEP;
	} else if ((wpa_ie_len != 0)) {
		if (((ieee->wpa_ie[0] == 0xdd) &&
		    (!memcmp(&(ieee->wpa_ie[14]), ccmp_ie, 4))) ||
		    ((ieee->wpa_ie[0] == 0x30) &&
		    (!memcmp(&ieee->wpa_ie[10], ccmp_rsn_ie, 4))))
			return SEC_ALG_CCMP;
		else
			return SEC_ALG_TKIP;
	} else {
		return SEC_ALG_NONE;
	}
}