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
typedef  int u16 ;

/* Variables and functions */
 int RTW_IEEE80211_FCTL_FROMDS ; 
 int RTW_IEEE80211_FCTL_TODS ; 
#define  RTW_IEEE80211_FTYPE_CTL 131 
#define  RTW_IEEE80211_FTYPE_DATA 130 
#define  RTW_IEEE80211_STYPE_ACK 129 
#define  RTW_IEEE80211_STYPE_CTS 128 
 int RTW_IEEE80211_STYPE_QOS_DATA ; 
 int /*<<< orphan*/  WLAN_FC_GET_STYPE (int) ; 
 int WLAN_FC_GET_TYPE (int) ; 

int ieee80211_get_hdrlen(u16 fc)
{
	int hdrlen = 24;

	switch (WLAN_FC_GET_TYPE(fc)) {
	case RTW_IEEE80211_FTYPE_DATA:
		if (fc & RTW_IEEE80211_STYPE_QOS_DATA)
			hdrlen += 2;
		if ((fc & RTW_IEEE80211_FCTL_FROMDS) && (fc & RTW_IEEE80211_FCTL_TODS))
			hdrlen += 6; /* Addr4 */
		break;
	case RTW_IEEE80211_FTYPE_CTL:
		switch (WLAN_FC_GET_STYPE(fc)) {
		case RTW_IEEE80211_STYPE_CTS:
		case RTW_IEEE80211_STYPE_ACK:
			hdrlen = 10;
			break;
		default:
			hdrlen = 16;
			break;
		}
		break;
	}

	return hdrlen;
}