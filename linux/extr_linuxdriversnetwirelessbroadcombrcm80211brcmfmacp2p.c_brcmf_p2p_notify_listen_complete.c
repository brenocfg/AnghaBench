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
struct brcmf_p2p_info {int /*<<< orphan*/  remain_on_channel; int /*<<< orphan*/  remain_on_channel_cookie; int /*<<< orphan*/  wait_next_af; int /*<<< orphan*/  status; } ;
struct brcmf_if {TYPE_1__* vif; TYPE_2__* drvr; } ;
struct brcmf_event_msg {int dummy; } ;
struct brcmf_cfg80211_info {struct brcmf_p2p_info p2p; } ;
struct TYPE_4__ {struct brcmf_cfg80211_info* config; } ;
struct TYPE_3__ {int /*<<< orphan*/  wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_P2P_STATUS_DISCOVER_LISTEN ; 
 int /*<<< orphan*/  BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME ; 
 int /*<<< orphan*/  BRCMF_P2P_STATUS_WAITING_NEXT_AF_LISTEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cfg80211_remain_on_channel_expired (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int brcmf_p2p_notify_listen_complete(struct brcmf_if *ifp,
				     const struct brcmf_event_msg *e,
				     void *data)
{
	struct brcmf_cfg80211_info *cfg = ifp->drvr->config;
	struct brcmf_p2p_info *p2p = &cfg->p2p;

	brcmf_dbg(TRACE, "Enter\n");
	if (test_and_clear_bit(BRCMF_P2P_STATUS_DISCOVER_LISTEN,
			       &p2p->status)) {
		if (test_and_clear_bit(BRCMF_P2P_STATUS_WAITING_NEXT_AF_LISTEN,
				       &p2p->status)) {
			clear_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME,
				  &p2p->status);
			brcmf_dbg(INFO, "Listen DONE, wake up wait_next_af\n");
			complete(&p2p->wait_next_af);
		}

		cfg80211_remain_on_channel_expired(&ifp->vif->wdev,
						   p2p->remain_on_channel_cookie,
						   &p2p->remain_on_channel,
						   GFP_KERNEL);
	}
	return 0;
}