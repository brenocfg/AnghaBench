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

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AC_VO ; 
 int IWL_MAX_TID_COUNT ; 
 int /*<<< orphan*/ * tid_to_mac80211_ac ; 

__attribute__((used)) static inline u8 iwl_mvm_tid_to_ac_queue(int tid)
{
	if (tid == IWL_MAX_TID_COUNT)
		return IEEE80211_AC_VO; /* MGMT */

	return tid_to_mac80211_ac[tid];
}