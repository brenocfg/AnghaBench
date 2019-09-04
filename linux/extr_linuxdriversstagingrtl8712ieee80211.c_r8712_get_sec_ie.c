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
typedef  size_t uint ;
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 size_t _BEACON_ITERVAL_ ; 
 size_t _CAPABILITY_ ; 
 size_t _TIMESTAMP_ ; 
 int _WPA2_IE_ID_ ; 
 int _WPA_IE_ID_ ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

int r8712_get_sec_ie(u8 *in_ie, uint in_len, u8 *rsn_ie, u16 *rsn_len,
		     u8 *wpa_ie, u16 *wpa_len)
{
	u8 authmode;
	u8 wpa_oui[4] = {0x0, 0x50, 0xf2, 0x01};
	uint cnt;

	/*Search required WPA or WPA2 IE and copy to sec_ie[ ]*/
	cnt = _TIMESTAMP_ + _BEACON_ITERVAL_ + _CAPABILITY_;
	while (cnt < in_len) {
		authmode = in_ie[cnt];
		if ((authmode == _WPA_IE_ID_) &&
		    (!memcmp(&in_ie[cnt + 2], &wpa_oui[0], 4))) {
			memcpy(wpa_ie, &in_ie[cnt], in_ie[cnt + 1] + 2);
			*wpa_len = in_ie[cnt + 1] + 2;
			cnt += in_ie[cnt + 1] + 2;  /*get next */
		} else {
			if (authmode == _WPA2_IE_ID_) {
				memcpy(rsn_ie, &in_ie[cnt],
				       in_ie[cnt + 1] + 2);
				*rsn_len = in_ie[cnt + 1] + 2;
				cnt += in_ie[cnt + 1] + 2;  /*get next*/
			} else {
				cnt += in_ie[cnt + 1] + 2;   /*get next*/
			}
		}
	}
	return *rsn_len + *wpa_len;
}