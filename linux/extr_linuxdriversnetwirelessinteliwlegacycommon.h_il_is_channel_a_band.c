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
struct il_channel_info {scalar_t__ band; } ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_5GHZ ; 

__attribute__((used)) static inline u8
il_is_channel_a_band(const struct il_channel_info *ch_info)
{
	return ch_info->band == NL80211_BAND_5GHZ;
}