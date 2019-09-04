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
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SP_Len ; 
 int /*<<< orphan*/  MFIE_TYPE_GENERIC ; 

__attribute__((used)) static void ieee80211_WMM_Info(struct ieee80211_device *ieee, u8 **tag_p)
{
	u8 *tag = *tag_p;

	*tag++ = MFIE_TYPE_GENERIC; /* 0 */
	*tag++ = 7;
	*tag++ = 0x00;
	*tag++ = 0x50;
	*tag++ = 0xf2;
	*tag++ = 0x02;	/* 5 */
	*tag++ = 0x00;
	*tag++ = 0x01;
#ifdef SUPPORT_USPD
	if (ieee->current_network.wmm_info & 0x80)
		*tag++ = 0x0f | MAX_SP_Len;
	else
		*tag++ = MAX_SP_Len;
#else
	*tag++ = MAX_SP_Len;
#endif
	*tag_p = tag;
}