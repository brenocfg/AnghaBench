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
struct TYPE_2__ {int bcast_id; } ;
struct il_priv {TYPE_1__ hw_params; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int IL_INVALID_STATION ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int il_sta_id (struct ieee80211_sta*) ; 

__attribute__((used)) static inline int
il_sta_id_or_broadcast(struct il_priv *il, struct ieee80211_sta *sta)
{
	int sta_id;

	if (!sta)
		return il->hw_params.bcast_id;

	sta_id = il_sta_id(sta);

	/*
	 * mac80211 should not be passing a partially
	 * initialised station!
	 */
	WARN_ON(sta_id == IL_INVALID_STATION);

	return sta_id;
}