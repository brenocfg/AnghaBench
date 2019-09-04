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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_SECONDARY_CHANNEL_OFFSET ; 
 int /*<<< orphan*/ * rtw_set_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

inline u8 *rtw_set_ie_secondary_ch_offset(u8 *buf, u32 *buf_len, u8 secondary_ch_offset)
{
	return rtw_set_ie(buf, WLAN_EID_SECONDARY_CHANNEL_OFFSET,  1, &secondary_ch_offset, buf_len);
}