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
typedef  scalar_t__ u8 ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_channel {int dummy; } ;
typedef  int __s8 ;

/* Variables and functions */

__attribute__((used)) static void ieee80211_find_cisco_dtpc(struct ieee80211_sub_if_data *sdata,
				      struct ieee80211_channel *channel,
				      const u8 *cisco_dtpc_ie,
				      int *pwr_level)
{
	/* From practical testing, the first data byte of the DTPC element
	 * seems to contain the requested dBm level, and the CLI on Cisco
	 * APs clearly state the range is -127 to 127 dBm, which indicates
	 * a signed byte, although it seemingly never actually goes negative.
	 * The other byte seems to always be zero.
	 */
	*pwr_level = (__s8)cisco_dtpc_ie[4];
}