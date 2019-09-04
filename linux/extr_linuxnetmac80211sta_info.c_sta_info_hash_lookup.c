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
typedef  int /*<<< orphan*/  u8 ;
struct rhlist_head {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  sta_hash; } ;

/* Variables and functions */
 struct rhlist_head* rhltable_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sta_rht_params ; 

struct rhlist_head *sta_info_hash_lookup(struct ieee80211_local *local,
					 const u8 *addr)
{
	return rhltable_lookup(&local->sta_hash, addr, sta_rht_params);
}