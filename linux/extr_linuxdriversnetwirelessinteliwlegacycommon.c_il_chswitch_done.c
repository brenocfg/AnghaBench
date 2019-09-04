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
struct il_priv {int /*<<< orphan*/  vif; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_CHANNEL_SWITCH_PENDING ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 int /*<<< orphan*/  ieee80211_chswitch_done (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
il_chswitch_done(struct il_priv *il, bool is_success)
{
	if (test_bit(S_EXIT_PENDING, &il->status))
		return;

	if (test_and_clear_bit(S_CHANNEL_SWITCH_PENDING, &il->status))
		ieee80211_chswitch_done(il->vif, is_success);
}