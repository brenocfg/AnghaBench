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
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct b43_wl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_update_templates (struct b43_wl*) ; 
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 

__attribute__((used)) static int b43_op_beacon_set_tim(struct ieee80211_hw *hw,
				 struct ieee80211_sta *sta, bool set)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);

	b43_update_templates(wl);

	return 0;
}