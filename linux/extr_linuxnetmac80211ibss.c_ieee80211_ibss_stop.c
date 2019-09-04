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
struct ieee80211_if_ibss {int /*<<< orphan*/  csa_connection_drop_work; } ;
struct TYPE_2__ {struct ieee80211_if_ibss ibss; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

void ieee80211_ibss_stop(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_ibss *ifibss = &sdata->u.ibss;

	cancel_work_sync(&ifibss->csa_connection_drop_work);
}