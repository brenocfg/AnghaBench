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
struct TYPE_2__ {int /*<<< orphan*/  deactivate; int /*<<< orphan*/  activate; int /*<<< orphan*/ * name; } ;
struct ieee80211_local {int /*<<< orphan*/ * tpt_led_trigger; TYPE_1__ tpt_led; int /*<<< orphan*/  tpt_led_active; TYPE_1__ radio_led; int /*<<< orphan*/  radio_led_active; TYPE_1__ assoc_led; int /*<<< orphan*/  assoc_led_active; TYPE_1__ tx_led; int /*<<< orphan*/  tx_led_active; TYPE_1__ rx_led; int /*<<< orphan*/  rx_led_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_assoc_led_activate ; 
 int /*<<< orphan*/  ieee80211_assoc_led_deactivate ; 
 int /*<<< orphan*/  ieee80211_radio_led_activate ; 
 int /*<<< orphan*/  ieee80211_radio_led_deactivate ; 
 int /*<<< orphan*/  ieee80211_rx_led_activate ; 
 int /*<<< orphan*/  ieee80211_rx_led_deactivate ; 
 int /*<<< orphan*/  ieee80211_tpt_led_activate ; 
 int /*<<< orphan*/  ieee80211_tpt_led_deactivate ; 
 int /*<<< orphan*/  ieee80211_tx_led_activate ; 
 int /*<<< orphan*/  ieee80211_tx_led_deactivate ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ led_trigger_register (TYPE_1__*) ; 

void ieee80211_led_init(struct ieee80211_local *local)
{
	atomic_set(&local->rx_led_active, 0);
	local->rx_led.activate = ieee80211_rx_led_activate;
	local->rx_led.deactivate = ieee80211_rx_led_deactivate;
	if (local->rx_led.name && led_trigger_register(&local->rx_led)) {
		kfree(local->rx_led.name);
		local->rx_led.name = NULL;
	}

	atomic_set(&local->tx_led_active, 0);
	local->tx_led.activate = ieee80211_tx_led_activate;
	local->tx_led.deactivate = ieee80211_tx_led_deactivate;
	if (local->tx_led.name && led_trigger_register(&local->tx_led)) {
		kfree(local->tx_led.name);
		local->tx_led.name = NULL;
	}

	atomic_set(&local->assoc_led_active, 0);
	local->assoc_led.activate = ieee80211_assoc_led_activate;
	local->assoc_led.deactivate = ieee80211_assoc_led_deactivate;
	if (local->assoc_led.name && led_trigger_register(&local->assoc_led)) {
		kfree(local->assoc_led.name);
		local->assoc_led.name = NULL;
	}

	atomic_set(&local->radio_led_active, 0);
	local->radio_led.activate = ieee80211_radio_led_activate;
	local->radio_led.deactivate = ieee80211_radio_led_deactivate;
	if (local->radio_led.name && led_trigger_register(&local->radio_led)) {
		kfree(local->radio_led.name);
		local->radio_led.name = NULL;
	}

	atomic_set(&local->tpt_led_active, 0);
	if (local->tpt_led_trigger) {
		local->tpt_led.activate = ieee80211_tpt_led_activate;
		local->tpt_led.deactivate = ieee80211_tpt_led_deactivate;
		if (led_trigger_register(&local->tpt_led)) {
			kfree(local->tpt_led_trigger);
			local->tpt_led_trigger = NULL;
		}
	}
}