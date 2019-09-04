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
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct ieee80211_reg_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MHZ_TO_KHZ (int) ; 
 struct ieee80211_reg_rule const* __freq_reg_info (struct wiphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const struct ieee80211_reg_rule *freq_reg_info(struct wiphy *wiphy,
					       u32 center_freq)
{
	return __freq_reg_info(wiphy, center_freq, MHZ_TO_KHZ(20));
}