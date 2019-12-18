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
struct ieee802_11_elems {TYPE_1__* mesh_config; } ;
struct TYPE_2__ {int meshconf_cap; } ;

/* Variables and functions */
 int IEEE80211_MESHCONF_CAPAB_TBTT_ADJUSTING ; 

__attribute__((used)) static bool mesh_peer_tbtt_adjusting(struct ieee802_11_elems *ie)
{
	return (ie->mesh_config->meshconf_cap &
			IEEE80211_MESHCONF_CAPAB_TBTT_ADJUSTING) != 0;
}