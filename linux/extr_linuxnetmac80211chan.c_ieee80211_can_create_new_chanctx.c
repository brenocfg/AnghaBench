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
struct ieee80211_local {int /*<<< orphan*/  chanctx_mtx; } ;

/* Variables and functions */
 scalar_t__ ieee80211_max_num_channels (struct ieee80211_local*) ; 
 scalar_t__ ieee80211_num_chanctx (struct ieee80211_local*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ieee80211_can_create_new_chanctx(struct ieee80211_local *local)
{
	lockdep_assert_held(&local->chanctx_mtx);
	return ieee80211_num_chanctx(local) < ieee80211_max_num_channels(local);
}