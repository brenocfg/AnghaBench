#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct brcmf_if {int /*<<< orphan*/  ndev; TYPE_1__* vif; TYPE_2__* drvr; } ;
struct brcmf_event_msg {scalar_t__ event_code; scalar_t__ status; } ;
struct brcmf_cfg80211_info {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {struct brcmf_cfg80211_info* config; } ;
struct TYPE_3__ {int /*<<< orphan*/  sme_state; } ;

/* Variables and functions */
 scalar_t__ BRCMF_E_ROAM ; 
 scalar_t__ BRCMF_E_STATUS_SUCCESS ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTED ; 
 int /*<<< orphan*/  brcmf_bss_connect_done (struct brcmf_cfg80211_info*,int /*<<< orphan*/ ,struct brcmf_event_msg const*,int) ; 
 int /*<<< orphan*/  brcmf_bss_roaming_done (struct brcmf_cfg80211_info*,int /*<<< orphan*/ ,struct brcmf_event_msg const*) ; 
 int /*<<< orphan*/  brcmf_net_setcarrier (struct brcmf_if*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32
brcmf_notify_roaming_status(struct brcmf_if *ifp,
			    const struct brcmf_event_msg *e, void *data)
{
	struct brcmf_cfg80211_info *cfg = ifp->drvr->config;
	u32 event = e->event_code;
	u32 status = e->status;

	if (event == BRCMF_E_ROAM && status == BRCMF_E_STATUS_SUCCESS) {
		if (test_bit(BRCMF_VIF_STATUS_CONNECTED,
			     &ifp->vif->sme_state)) {
			brcmf_bss_roaming_done(cfg, ifp->ndev, e);
		} else {
			brcmf_bss_connect_done(cfg, ifp->ndev, e, true);
			brcmf_net_setcarrier(ifp, true);
		}
	}

	return 0;
}