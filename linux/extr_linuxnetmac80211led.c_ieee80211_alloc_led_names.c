#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_7__ {void* name; } ;
struct TYPE_6__ {void* name; } ;
struct TYPE_10__ {void* name; } ;
struct TYPE_8__ {void* name; } ;
struct ieee80211_local {TYPE_4__ hw; TYPE_2__ radio_led; TYPE_1__ assoc_led; TYPE_5__ tx_led; TYPE_3__ rx_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

void ieee80211_alloc_led_names(struct ieee80211_local *local)
{
	local->rx_led.name = kasprintf(GFP_KERNEL, "%srx",
				       wiphy_name(local->hw.wiphy));
	local->tx_led.name = kasprintf(GFP_KERNEL, "%stx",
				       wiphy_name(local->hw.wiphy));
	local->assoc_led.name = kasprintf(GFP_KERNEL, "%sassoc",
					  wiphy_name(local->hw.wiphy));
	local->radio_led.name = kasprintf(GFP_KERNEL, "%sradio",
					  wiphy_name(local->hw.wiphy));
}