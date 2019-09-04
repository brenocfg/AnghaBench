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
struct ieee80211_vif {int* hw_queue; scalar_t__ type; scalar_t__ cab_queue; } ;
struct ieee80211_hw {scalar_t__ queues; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_INVAL_HW_QUEUE ; 
 int IEEE80211_NUM_ACS ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  ath9k_is_chanctx_enabled () ; 

__attribute__((used)) static void ath9k_assign_hw_queues(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif)
{
	int i;

	if (!ath9k_is_chanctx_enabled())
		return;

	for (i = 0; i < IEEE80211_NUM_ACS; i++)
		vif->hw_queue[i] = i;

	if (vif->type == NL80211_IFTYPE_AP ||
	    vif->type == NL80211_IFTYPE_MESH_POINT)
		vif->cab_queue = hw->queues - 2;
	else
		vif->cab_queue = IEEE80211_INVAL_HW_QUEUE;
}