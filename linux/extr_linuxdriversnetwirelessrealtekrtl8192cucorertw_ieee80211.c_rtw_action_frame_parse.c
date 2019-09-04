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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rtw_ieee80211_hdr_3addr {int /*<<< orphan*/  frame_ctl; } ;

/* Variables and functions */
 int ACT_PUBLIC_MAX ; 
 int RTW_IEEE80211_FCTL_FTYPE ; 
 int RTW_IEEE80211_FCTL_STYPE ; 
 int RTW_IEEE80211_FTYPE_MGMT ; 
 int RTW_IEEE80211_STYPE_ACTION ; 
#define  RTW_WLAN_CATEGORY_P2P 128 
 int _FALSE ; 
 int _TRUE ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

int rtw_action_frame_parse(const u8 *frame, u32 frame_len, u8* category, u8 *action)
{
	const u8 *frame_body = frame + sizeof(struct rtw_ieee80211_hdr_3addr);
	u16 fc;
	u8 c;
	u8 a = ACT_PUBLIC_MAX;

	fc = le16_to_cpu(((struct rtw_ieee80211_hdr_3addr *)frame)->frame_ctl);

	if ((fc & (RTW_IEEE80211_FCTL_FTYPE|RTW_IEEE80211_FCTL_STYPE))
		!= (RTW_IEEE80211_FTYPE_MGMT|RTW_IEEE80211_STYPE_ACTION)
	)
	{
		return _FALSE;
	}

	c = frame_body[0];

	switch(c) {
	case RTW_WLAN_CATEGORY_P2P: /* vendor-specific */
		break;
	default:
		a = frame_body[1];
	}

	if (category)
		*category = c;
	if (action)
		*action = a;

	return _TRUE;
}