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
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int RTW_2G_CHANNELS_NUM ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 scalar_t__ rtw_2ghz_channels ; 

__attribute__((used)) static void rtw_2g_channels_init(struct ieee80211_channel *channels)
{
	memcpy((void*)channels, (void*)rtw_2ghz_channels,
		sizeof(struct ieee80211_channel)*RTW_2G_CHANNELS_NUM
	);
}