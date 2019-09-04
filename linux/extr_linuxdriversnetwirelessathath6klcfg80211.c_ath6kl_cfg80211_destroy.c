#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath6kl {int /*<<< orphan*/  wiphy; TYPE_1__* sta_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  aggr_conn; } ;

/* Variables and functions */
 int AP_MAX_NUM_STA ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_free (int /*<<< orphan*/ ) ; 

void ath6kl_cfg80211_destroy(struct ath6kl *ar)
{
	int i;

	for (i = 0; i < AP_MAX_NUM_STA; i++)
		kfree(ar->sta_list[i].aggr_conn);

	wiphy_free(ar->wiphy);
}