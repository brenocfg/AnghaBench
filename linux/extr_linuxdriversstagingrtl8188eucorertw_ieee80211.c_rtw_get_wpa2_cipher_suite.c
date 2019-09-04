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
 int /*<<< orphan*/  RSN_CIPHER_SUITE_CCMP ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_NONE ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_TKIP ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_WEP104 ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_WEP40 ; 
 int /*<<< orphan*/  RSN_SELECTOR_LEN ; 
 int WPA_CIPHER_CCMP ; 
 int WPA_CIPHER_NONE ; 
 int WPA_CIPHER_TKIP ; 
 int WPA_CIPHER_WEP104 ; 
 int WPA_CIPHER_WEP40 ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtw_get_wpa2_cipher_suite(u8 *s)
{
	if (!memcmp(s, RSN_CIPHER_SUITE_NONE, RSN_SELECTOR_LEN))
		return WPA_CIPHER_NONE;
	if (!memcmp(s, RSN_CIPHER_SUITE_WEP40, RSN_SELECTOR_LEN))
		return WPA_CIPHER_WEP40;
	if (!memcmp(s, RSN_CIPHER_SUITE_TKIP, RSN_SELECTOR_LEN))
		return WPA_CIPHER_TKIP;
	if (!memcmp(s, RSN_CIPHER_SUITE_CCMP, RSN_SELECTOR_LEN))
		return WPA_CIPHER_CCMP;
	if (!memcmp(s, RSN_CIPHER_SUITE_WEP104, RSN_SELECTOR_LEN))
		return WPA_CIPHER_WEP104;

	return 0;
}