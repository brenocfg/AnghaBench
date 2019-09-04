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
struct sta_info {int /*<<< orphan*/  hash_node; } ;
struct ieee80211_local {int /*<<< orphan*/  sta_hash; } ;

/* Variables and functions */
 int rhltable_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sta_rht_params ; 

__attribute__((used)) static int sta_info_hash_del(struct ieee80211_local *local,
			     struct sta_info *sta)
{
	return rhltable_remove(&local->sta_hash, &sta->hash_node,
			       sta_rht_params);
}