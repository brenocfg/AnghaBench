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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int WPA_CIPHER_CCMP ; 
 int WPA_CIPHER_NONE ; 
 int /*<<< orphan*/  WPA_CIPHER_SUITE_CCMP ; 
 int /*<<< orphan*/  WPA_CIPHER_SUITE_NONE ; 
 int /*<<< orphan*/  WPA_CIPHER_SUITE_TKIP ; 
 int /*<<< orphan*/  WPA_CIPHER_SUITE_WEP104 ; 
 int /*<<< orphan*/  WPA_CIPHER_SUITE_WEP40 ; 
 int WPA_CIPHER_TKIP ; 
 int WPA_CIPHER_WEP104 ; 
 int WPA_CIPHER_WEP40 ; 
 int /*<<< orphan*/  WPA_SELECTOR_LEN ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtw_get_wpa_cipher_suite(u8 *s)
{
	if (!memcmp(s, WPA_CIPHER_SUITE_NONE, WPA_SELECTOR_LEN))
		return WPA_CIPHER_NONE;
	if (!memcmp(s, WPA_CIPHER_SUITE_WEP40, WPA_SELECTOR_LEN))
		return WPA_CIPHER_WEP40;
	if (!memcmp(s, WPA_CIPHER_SUITE_TKIP, WPA_SELECTOR_LEN))
		return WPA_CIPHER_TKIP;
	if (!memcmp(s, WPA_CIPHER_SUITE_CCMP, WPA_SELECTOR_LEN))
		return WPA_CIPHER_CCMP;
	if (!memcmp(s, WPA_CIPHER_SUITE_WEP104, WPA_SELECTOR_LEN))
		return WPA_CIPHER_WEP104;

	return 0;
}