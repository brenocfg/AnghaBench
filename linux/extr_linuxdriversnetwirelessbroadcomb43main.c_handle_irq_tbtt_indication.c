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
struct b43_wldev {int dfq_valid; int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 scalar_t__ b43_is_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_power_saving_ctl_bits (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_irq_tbtt_indication(struct b43_wldev *dev)
{
	if (b43_is_mode(dev->wl, NL80211_IFTYPE_AP)) {
		///TODO: PS TBTT
	} else {
		if (1 /*FIXME: the last PSpoll frame was sent successfully */ )
			b43_power_saving_ctl_bits(dev, 0);
	}
	if (b43_is_mode(dev->wl, NL80211_IFTYPE_ADHOC))
		dev->dfq_valid = true;
}