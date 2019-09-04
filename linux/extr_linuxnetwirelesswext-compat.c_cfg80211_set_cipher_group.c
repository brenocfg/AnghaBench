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
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ cipher_group; } ;
struct TYPE_4__ {TYPE_3__ crypto; } ;
struct TYPE_5__ {TYPE_1__ connect; } ;
struct wireless_dev {TYPE_2__ wext; } ;

/* Variables and functions */
 int EINVAL ; 
 int IW_AUTH_CIPHER_AES_CMAC ; 
 int IW_AUTH_CIPHER_CCMP ; 
 int IW_AUTH_CIPHER_NONE ; 
 int IW_AUTH_CIPHER_TKIP ; 
 int IW_AUTH_CIPHER_WEP104 ; 
 int IW_AUTH_CIPHER_WEP40 ; 
 scalar_t__ WLAN_CIPHER_SUITE_AES_CMAC ; 
 scalar_t__ WLAN_CIPHER_SUITE_CCMP ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 

__attribute__((used)) static int cfg80211_set_cipher_group(struct wireless_dev *wdev, u32 cipher)
{
	if (cipher & IW_AUTH_CIPHER_WEP40)
		wdev->wext.connect.crypto.cipher_group =
			WLAN_CIPHER_SUITE_WEP40;
	else if (cipher & IW_AUTH_CIPHER_WEP104)
		wdev->wext.connect.crypto.cipher_group =
			WLAN_CIPHER_SUITE_WEP104;
	else if (cipher & IW_AUTH_CIPHER_TKIP)
		wdev->wext.connect.crypto.cipher_group =
			WLAN_CIPHER_SUITE_TKIP;
	else if (cipher & IW_AUTH_CIPHER_CCMP)
		wdev->wext.connect.crypto.cipher_group =
			WLAN_CIPHER_SUITE_CCMP;
	else if (cipher & IW_AUTH_CIPHER_AES_CMAC)
		wdev->wext.connect.crypto.cipher_group =
			WLAN_CIPHER_SUITE_AES_CMAC;
	else if (cipher & IW_AUTH_CIPHER_NONE)
		wdev->wext.connect.crypto.cipher_group = 0;
	else
		return -EINVAL;

	return 0;
}