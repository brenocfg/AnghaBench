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
struct cw1200_ht_info {scalar_t__ channel_type; } ;

/* Variables and functions */
 scalar_t__ NL80211_CHAN_NO_HT ; 

__attribute__((used)) static inline int cw1200_is_ht(const struct cw1200_ht_info *ht_info)
{
	return ht_info->channel_type != NL80211_CHAN_NO_HT;
}