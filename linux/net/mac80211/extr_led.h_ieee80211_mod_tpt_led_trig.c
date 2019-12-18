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
struct ieee80211_local {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void ieee80211_mod_tpt_led_trig(struct ieee80211_local *local,
					      unsigned int types_on,
					      unsigned int types_off)
{
}