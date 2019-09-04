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
struct wiphy {int dummy; } ;
struct ieee80211_reg_rule {int flags; } ;
struct ieee80211_channel {int flags; int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int IEEE80211_CHAN_NO_IR ; 
 scalar_t__ IS_ERR (struct ieee80211_reg_rule const*) ; 
 int /*<<< orphan*/  MHZ_TO_KHZ (int /*<<< orphan*/ ) ; 
 int NL80211_RRF_NO_IR ; 
 struct ieee80211_reg_rule* freq_reg_info (struct wiphy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath_force_clear_no_ir_chan(struct wiphy *wiphy,
				       struct ieee80211_channel *ch)
{
	const struct ieee80211_reg_rule *reg_rule;

	reg_rule = freq_reg_info(wiphy, MHZ_TO_KHZ(ch->center_freq));
	if (IS_ERR(reg_rule))
		return;

	if (!(reg_rule->flags & NL80211_RRF_NO_IR))
		if (ch->flags & IEEE80211_CHAN_NO_IR)
			ch->flags &= ~IEEE80211_CHAN_NO_IR;
}