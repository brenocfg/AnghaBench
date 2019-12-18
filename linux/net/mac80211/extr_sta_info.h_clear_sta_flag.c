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
struct sta_info {int /*<<< orphan*/  _flags; } ;
typedef  enum ieee80211_sta_info_flags { ____Placeholder_ieee80211_sta_info_flags } ieee80211_sta_info_flags ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WLAN_STA_ASSOC ; 
 int WLAN_STA_AUTH ; 
 int WLAN_STA_AUTHORIZED ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void clear_sta_flag(struct sta_info *sta,
				  enum ieee80211_sta_info_flags flag)
{
	WARN_ON(flag == WLAN_STA_AUTH ||
		flag == WLAN_STA_ASSOC ||
		flag == WLAN_STA_AUTHORIZED);
	clear_bit(flag, &sta->_flags);
}