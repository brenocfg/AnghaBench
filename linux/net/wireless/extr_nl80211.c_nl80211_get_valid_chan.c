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
struct nlattr {int dummy; } ;
struct ieee80211_channel {int flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static struct ieee80211_channel *nl80211_get_valid_chan(struct wiphy *wiphy,
							struct nlattr *tb)
{
	struct ieee80211_channel *chan;

	if (tb == NULL)
		return NULL;
	chan = ieee80211_get_channel(wiphy, nla_get_u32(tb));
	if (!chan || chan->flags & IEEE80211_CHAN_DISABLED)
		return NULL;
	return chan;
}