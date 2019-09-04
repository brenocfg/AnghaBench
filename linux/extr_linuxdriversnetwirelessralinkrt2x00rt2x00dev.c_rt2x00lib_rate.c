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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_rate {int flags; int /*<<< orphan*/  bitrate; } ;
struct ieee80211_rate {int /*<<< orphan*/  flags; int /*<<< orphan*/  hw_value_short; int /*<<< orphan*/  hw_value; int /*<<< orphan*/  bitrate; } ;

/* Variables and functions */
 int DEV_RATE_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  IEEE80211_RATE_SHORT_PREAMBLE ; 

__attribute__((used)) static void rt2x00lib_rate(struct ieee80211_rate *entry,
			   const u16 index, const struct rt2x00_rate *rate)
{
	entry->flags = 0;
	entry->bitrate = rate->bitrate;
	entry->hw_value = index;
	entry->hw_value_short = index;

	if (rate->flags & DEV_RATE_SHORT_PREAMBLE)
		entry->flags |= IEEE80211_RATE_SHORT_PREAMBLE;
}