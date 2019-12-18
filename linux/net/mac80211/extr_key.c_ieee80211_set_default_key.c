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
struct ieee80211_sub_if_data {TYPE_1__* local; } ;
struct TYPE_2__ {int /*<<< orphan*/  key_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ieee80211_set_default_key (struct ieee80211_sub_if_data*,int,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ieee80211_set_default_key(struct ieee80211_sub_if_data *sdata, int idx,
			       bool uni, bool multi)
{
	mutex_lock(&sdata->local->key_mtx);
	__ieee80211_set_default_key(sdata, idx, uni, multi);
	mutex_unlock(&sdata->local->key_mtx);
}