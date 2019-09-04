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
struct sta_info {int dummy; } ;
typedef  enum nl80211_plink_state { ____Placeholder_nl80211_plink_state } nl80211_plink_state ;

/* Variables and functions */
 int NL80211_PLINK_LISTEN ; 

__attribute__((used)) static inline enum nl80211_plink_state sta_plink_state(struct sta_info *sta)
{
#ifdef CONFIG_MAC80211_MESH
	return sta->mesh->plink_state;
#endif
	return NL80211_PLINK_LISTEN;
}