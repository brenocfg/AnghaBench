#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ conf; } ;
struct ieee80211_local {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_IDLE ; 
 int IEEE80211_CONF_IDLE ; 

__attribute__((used)) static u32 __ieee80211_idle_off(struct ieee80211_local *local)
{
	if (!(local->hw.conf.flags & IEEE80211_CONF_IDLE))
		return 0;

	local->hw.conf.flags &= ~IEEE80211_CONF_IDLE;
	return IEEE80211_CONF_CHANGE_IDLE;
}