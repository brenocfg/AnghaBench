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
struct rate_control_ref {int dummy; } ;
struct ieee80211_local {struct rate_control_ref* rate_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  rate_control_free (struct ieee80211_local*,struct rate_control_ref*) ; 

void rate_control_deinitialize(struct ieee80211_local *local)
{
	struct rate_control_ref *ref;

	ref = local->rate_ctrl;

	if (!ref)
		return;

	local->rate_ctrl = NULL;
	rate_control_free(local, ref);
}