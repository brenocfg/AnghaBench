#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_local {scalar_t__ hw_scan_band; TYPE_3__* hw_scan_req; int /*<<< orphan*/  hw_scan_ies_bufsize; int /*<<< orphan*/  hw; int /*<<< orphan*/  scanning; int /*<<< orphan*/  mtx; int /*<<< orphan*/  scan_req; } ;
struct cfg80211_scan_request {int n_channels; int flags; int /*<<< orphan*/  bssid; int /*<<< orphan*/  mac_addr_mask; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  no_cck; int /*<<< orphan*/  rates; int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; int /*<<< orphan*/  scan_width; TYPE_1__** channels; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_5__ {int n_channels; int ie_len; int /*<<< orphan*/  bssid; int /*<<< orphan*/  mac_addr_mask; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  no_cck; scalar_t__ ie; TYPE_1__** channels; } ;
struct TYPE_6__ {TYPE_2__ req; int /*<<< orphan*/  ies; } ;
struct TYPE_4__ {scalar_t__ band; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int /*<<< orphan*/  IEEE80211_PROBE_FLAG_MIN_CONTENT ; 
 int NL80211_SCAN_FLAG_MIN_PREQ_CONTENT ; 
 scalar_t__ NUM_NL80211_BANDS ; 
 int /*<<< orphan*/  SCAN_HW_CANCELLED ; 
 int /*<<< orphan*/  SINGLE_SCAN_ON_ALL_BANDS ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_build_preq_ies (struct ieee80211_local*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_chan_def*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_prepare_scan_chandef (struct cfg80211_chan_def*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct cfg80211_scan_request* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ieee80211_prep_hw_scan(struct ieee80211_local *local)
{
	struct cfg80211_scan_request *req;
	struct cfg80211_chan_def chandef;
	u8 bands_used = 0;
	int i, ielen, n_chans;
	u32 flags = 0;

	req = rcu_dereference_protected(local->scan_req,
					lockdep_is_held(&local->mtx));

	if (test_bit(SCAN_HW_CANCELLED, &local->scanning))
		return false;

	if (ieee80211_hw_check(&local->hw, SINGLE_SCAN_ON_ALL_BANDS)) {
		for (i = 0; i < req->n_channels; i++) {
			local->hw_scan_req->req.channels[i] = req->channels[i];
			bands_used |= BIT(req->channels[i]->band);
		}

		n_chans = req->n_channels;
	} else {
		do {
			if (local->hw_scan_band == NUM_NL80211_BANDS)
				return false;

			n_chans = 0;

			for (i = 0; i < req->n_channels; i++) {
				if (req->channels[i]->band !=
				    local->hw_scan_band)
					continue;
				local->hw_scan_req->req.channels[n_chans] =
							req->channels[i];
				n_chans++;
				bands_used |= BIT(req->channels[i]->band);
			}

			local->hw_scan_band++;
		} while (!n_chans);
	}

	local->hw_scan_req->req.n_channels = n_chans;
	ieee80211_prepare_scan_chandef(&chandef, req->scan_width);

	if (req->flags & NL80211_SCAN_FLAG_MIN_PREQ_CONTENT)
		flags |= IEEE80211_PROBE_FLAG_MIN_CONTENT;

	ielen = ieee80211_build_preq_ies(local,
					 (u8 *)local->hw_scan_req->req.ie,
					 local->hw_scan_ies_bufsize,
					 &local->hw_scan_req->ies,
					 req->ie, req->ie_len,
					 bands_used, req->rates, &chandef,
					 flags);
	local->hw_scan_req->req.ie_len = ielen;
	local->hw_scan_req->req.no_cck = req->no_cck;
	ether_addr_copy(local->hw_scan_req->req.mac_addr, req->mac_addr);
	ether_addr_copy(local->hw_scan_req->req.mac_addr_mask,
			req->mac_addr_mask);
	ether_addr_copy(local->hw_scan_req->req.bssid, req->bssid);

	return true;
}