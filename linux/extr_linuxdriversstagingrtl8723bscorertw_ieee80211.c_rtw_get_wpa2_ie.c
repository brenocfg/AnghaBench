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

/* Variables and functions */
 int /*<<< orphan*/  _WPA2_IE_ID_ ; 
 unsigned char* rtw_get_ie (unsigned char*,int /*<<< orphan*/ ,int*,int) ; 

unsigned char *rtw_get_wpa2_ie(unsigned char *pie, int *rsn_ie_len, int limit)
{
	return rtw_get_ie(pie, _WPA2_IE_ID_, rsn_ie_len, limit);
}