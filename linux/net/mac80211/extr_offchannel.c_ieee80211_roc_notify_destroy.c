#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_roc_work {int /*<<< orphan*/  list; int /*<<< orphan*/  chan; int /*<<< orphan*/  mgmt_tx_cookie; TYPE_2__* sdata; int /*<<< orphan*/  cookie; TYPE_3__* frame; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  wdev; TYPE_1__* local; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfg80211_mgmt_tx_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_remain_on_channel_expired (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_tx_mgmt_expired (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_roc_work*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_roc_notify_destroy(struct ieee80211_roc_work *roc)
{
	/* was never transmitted */
	if (roc->frame) {
		cfg80211_mgmt_tx_status(&roc->sdata->wdev, roc->mgmt_tx_cookie,
					roc->frame->data, roc->frame->len,
					false, GFP_KERNEL);
		ieee80211_free_txskb(&roc->sdata->local->hw, roc->frame);
	}

	if (!roc->mgmt_tx_cookie)
		cfg80211_remain_on_channel_expired(&roc->sdata->wdev,
						   roc->cookie, roc->chan,
						   GFP_KERNEL);
	else
		cfg80211_tx_mgmt_expired(&roc->sdata->wdev,
					 roc->mgmt_tx_cookie,
					 roc->chan, GFP_KERNEL);

	list_del(&roc->list);
	kfree(roc);
}