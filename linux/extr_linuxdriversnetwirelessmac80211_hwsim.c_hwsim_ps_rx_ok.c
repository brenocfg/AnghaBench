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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct mac80211_hwsim_data {int ps; int ps_poll_pending; } ;

/* Variables and functions */
#define  PS_AUTO_POLL 131 
#define  PS_DISABLED 130 
#define  PS_ENABLED 129 
#define  PS_MANUAL_POLL 128 
 int /*<<< orphan*/  mac80211_hwsim_addr_match (struct mac80211_hwsim_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hwsim_ps_rx_ok(struct mac80211_hwsim_data *data,
			   struct sk_buff *skb)
{
	switch (data->ps) {
	case PS_DISABLED:
		return true;
	case PS_ENABLED:
		return false;
	case PS_AUTO_POLL:
		/* TODO: accept (some) Beacons by default and other frames only
		 * if pending PS-Poll has been sent */
		return true;
	case PS_MANUAL_POLL:
		/* Allow unicast frames to own address if there is a pending
		 * PS-Poll */
		if (data->ps_poll_pending &&
		    mac80211_hwsim_addr_match(data, skb->data + 4)) {
			data->ps_poll_pending = false;
			return true;
		}
		return false;
	}

	return true;
}