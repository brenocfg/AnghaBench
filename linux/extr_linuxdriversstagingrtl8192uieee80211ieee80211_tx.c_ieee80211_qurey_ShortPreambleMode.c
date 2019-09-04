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
struct TYPE_2__ {int capability; } ;
struct ieee80211_device {TYPE_1__ current_network; } ;
struct cb_desc {int bUseShortPreamble; int data_rate; } ;

/* Variables and functions */
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 

__attribute__((used)) static void ieee80211_qurey_ShortPreambleMode(struct ieee80211_device *ieee,
					      struct cb_desc *tcb_desc)
{
	tcb_desc->bUseShortPreamble = false;
	if (tcb_desc->data_rate == 2)
	{//// 1M can only use Long Preamble. 11B spec
		return;
	}
	else if (ieee->current_network.capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
	{
		tcb_desc->bUseShortPreamble = true;
	}
	return;
}