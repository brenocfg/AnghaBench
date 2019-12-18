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
struct ieee80211_local {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iterate_stations (struct ieee80211_local*,void (*) (void*,struct ieee80211_sta*),void*) ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void ieee80211_iterate_stations_atomic(struct ieee80211_hw *hw,
			void (*iterator)(void *data,
					 struct ieee80211_sta *sta),
			void *data)
{
	struct ieee80211_local *local = hw_to_local(hw);

	rcu_read_lock();
	__iterate_stations(local, iterator, data);
	rcu_read_unlock();
}