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
struct ieee80211_local {int /*<<< orphan*/  roc_list; int /*<<< orphan*/  roc_work; int /*<<< orphan*/  hw_roc_done; int /*<<< orphan*/  hw_roc_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_hw_roc_done ; 
 int /*<<< orphan*/  ieee80211_hw_roc_start ; 
 int /*<<< orphan*/  ieee80211_roc_work ; 

void ieee80211_roc_setup(struct ieee80211_local *local)
{
	INIT_WORK(&local->hw_roc_start, ieee80211_hw_roc_start);
	INIT_WORK(&local->hw_roc_done, ieee80211_hw_roc_done);
	INIT_DELAYED_WORK(&local->roc_work, ieee80211_roc_work);
	INIT_LIST_HEAD(&local->roc_list);
}