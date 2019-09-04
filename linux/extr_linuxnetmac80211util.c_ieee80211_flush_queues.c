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
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ieee80211_flush_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int) ; 

void ieee80211_flush_queues(struct ieee80211_local *local,
			    struct ieee80211_sub_if_data *sdata, bool drop)
{
	__ieee80211_flush_queues(local, sdata, 0, drop);
}