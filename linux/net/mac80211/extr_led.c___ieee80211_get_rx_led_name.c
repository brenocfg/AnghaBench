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
struct TYPE_2__ {char const* name; } ;
struct ieee80211_local {TYPE_1__ rx_led; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 

const char *__ieee80211_get_rx_led_name(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	return local->rx_led.name;
}