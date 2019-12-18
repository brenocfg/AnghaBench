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
typedef  scalar_t__ u64 ;
struct ieee80211_local {scalar_t__ roc_cookie_counter; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

u64 ieee80211_mgmt_tx_cookie(struct ieee80211_local *local)
{
	lockdep_assert_held(&local->mtx);

	local->roc_cookie_counter++;

	/* wow, you wrapped 64 bits ... more likely a bug */
	if (WARN_ON(local->roc_cookie_counter == 0))
		local->roc_cookie_counter++;

	return local->roc_cookie_counter;
}