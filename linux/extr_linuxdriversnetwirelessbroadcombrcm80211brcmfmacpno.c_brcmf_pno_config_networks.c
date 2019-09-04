#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cfg80211_sched_scan_request {int n_match_sets; struct cfg80211_match_set* match_sets; } ;
struct TYPE_3__ {scalar_t__ ssid_len; } ;
struct cfg80211_match_set {int /*<<< orphan*/  bssid; TYPE_1__ ssid; } ;
struct brcmf_pno_info {int n_reqs; struct cfg80211_sched_scan_request** reqs; } ;
struct brcmf_if {int dummy; } ;

/* Variables and functions */
 int brcmf_is_ssid_active (TYPE_1__*,struct cfg80211_sched_scan_request*) ; 
 int brcmf_pno_add_bssid (struct brcmf_if*,int /*<<< orphan*/ ) ; 
 int brcmf_pno_add_ssid (struct brcmf_if*,TYPE_1__*,int) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_pno_config_networks(struct brcmf_if *ifp,
				     struct brcmf_pno_info *pi)
{
	struct cfg80211_sched_scan_request *r;
	struct cfg80211_match_set *ms;
	bool active;
	int i, j, err = 0;

	for (i = 0; i < pi->n_reqs; i++) {
		r = pi->reqs[i];

		for (j = 0; j < r->n_match_sets; j++) {
			ms = &r->match_sets[j];
			if (ms->ssid.ssid_len) {
				active = brcmf_is_ssid_active(&ms->ssid, r);
				err = brcmf_pno_add_ssid(ifp, &ms->ssid,
							 active);
			}
			if (!err && is_valid_ether_addr(ms->bssid))
				err = brcmf_pno_add_bssid(ifp, ms->bssid);

			if (err < 0)
				return err;
		}
	}
	return 0;
}