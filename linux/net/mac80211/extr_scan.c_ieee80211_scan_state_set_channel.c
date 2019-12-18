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
struct TYPE_2__ {int /*<<< orphan*/  width; struct ieee80211_channel* chan; scalar_t__ center_freq2; int /*<<< orphan*/  center_freq1; } ;
struct ieee80211_local {size_t scan_channel_idx; void* next_scan_state; TYPE_1__ scan_chandef; TYPE_1__ _oper_chandef; int /*<<< orphan*/  mtx; int /*<<< orphan*/  scan_req; } ;
struct ieee80211_channel {int flags; int /*<<< orphan*/  center_freq; } ;
struct cfg80211_scan_request {int scan_width; int /*<<< orphan*/  n_ssids; struct ieee80211_channel** channels; } ;
typedef  enum nl80211_bss_scan_width { ____Placeholder_nl80211_bss_scan_width } nl80211_bss_scan_width ;

/* Variables and functions */
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_CHANNEL ; 
 unsigned long IEEE80211_PASSIVE_CHANNEL_TIME ; 
 unsigned long IEEE80211_PROBE_DELAY ; 
#define  NL80211_BSS_CHAN_WIDTH_10 130 
#define  NL80211_BSS_CHAN_WIDTH_20 129 
#define  NL80211_BSS_CHAN_WIDTH_5 128 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_10 ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_20_NOHT ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_5 ; 
 void* SCAN_DECISION ; 
 void* SCAN_SEND_PROBE ; 
 int cfg80211_chandef_to_scan_width (TYPE_1__*) ; 
 scalar_t__ ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct cfg80211_scan_request* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_scan_state_set_channel(struct ieee80211_local *local,
					     unsigned long *next_delay)
{
	int skip;
	struct ieee80211_channel *chan;
	enum nl80211_bss_scan_width oper_scan_width;
	struct cfg80211_scan_request *scan_req;

	scan_req = rcu_dereference_protected(local->scan_req,
					     lockdep_is_held(&local->mtx));

	skip = 0;
	chan = scan_req->channels[local->scan_channel_idx];

	local->scan_chandef.chan = chan;
	local->scan_chandef.center_freq1 = chan->center_freq;
	local->scan_chandef.center_freq2 = 0;
	switch (scan_req->scan_width) {
	case NL80211_BSS_CHAN_WIDTH_5:
		local->scan_chandef.width = NL80211_CHAN_WIDTH_5;
		break;
	case NL80211_BSS_CHAN_WIDTH_10:
		local->scan_chandef.width = NL80211_CHAN_WIDTH_10;
		break;
	case NL80211_BSS_CHAN_WIDTH_20:
		/* If scanning on oper channel, use whatever channel-type
		 * is currently in use.
		 */
		oper_scan_width = cfg80211_chandef_to_scan_width(
					&local->_oper_chandef);
		if (chan == local->_oper_chandef.chan &&
		    oper_scan_width == scan_req->scan_width)
			local->scan_chandef = local->_oper_chandef;
		else
			local->scan_chandef.width = NL80211_CHAN_WIDTH_20_NOHT;
		break;
	}

	if (ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_CHANNEL))
		skip = 1;

	/* advance state machine to next channel/band */
	local->scan_channel_idx++;

	if (skip) {
		/* if we skip this channel return to the decision state */
		local->next_scan_state = SCAN_DECISION;
		return;
	}

	/*
	 * Probe delay is used to update the NAV, cf. 11.1.3.2.2
	 * (which unfortunately doesn't say _why_ step a) is done,
	 * but it waits for the probe delay or until a frame is
	 * received - and the received frame would update the NAV).
	 * For now, we do not support waiting until a frame is
	 * received.
	 *
	 * In any case, it is not necessary for a passive scan.
	 */
	if ((chan->flags & (IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_RADAR)) ||
	    !scan_req->n_ssids) {
		*next_delay = IEEE80211_PASSIVE_CHANNEL_TIME;
		local->next_scan_state = SCAN_DECISION;
		return;
	}

	/* active scan, send probes */
	*next_delay = IEEE80211_PROBE_DELAY;
	local->next_scan_state = SCAN_SEND_PROBE;
}