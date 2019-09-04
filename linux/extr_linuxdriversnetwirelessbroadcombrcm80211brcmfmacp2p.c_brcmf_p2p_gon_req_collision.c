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
struct TYPE_6__ {int /*<<< orphan*/  act_frm_scan; } ;
struct brcmf_p2p_info {int block_gon_req_tx; int /*<<< orphan*/  status; TYPE_3__ afx_hdl; TYPE_2__* bss_idx; int /*<<< orphan*/  gon_req_action; struct brcmf_cfg80211_info* cfg; } ;
struct brcmf_if {int /*<<< orphan*/  mac_addr; } ;
struct brcmf_cfg80211_info {int dummy; } ;
struct TYPE_5__ {TYPE_1__* vif; } ;
struct TYPE_4__ {struct brcmf_if* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL ; 
 int /*<<< orphan*/  BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INFO ; 
 size_t P2PAPI_BSSCFG_DEVICE ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_p2p_stop_wait_next_action_frame (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
brcmf_p2p_gon_req_collision(struct brcmf_p2p_info *p2p, u8 *mac)
{
	struct brcmf_cfg80211_info *cfg = p2p->cfg;
	struct brcmf_if *ifp;

	brcmf_dbg(TRACE, "Enter\n");

	if (!test_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME, &p2p->status) ||
	    !p2p->gon_req_action)
		return false;

	brcmf_dbg(TRACE, "GO Negotiation Request COLLISION !!!\n");
	/* if sa(peer) addr is less than da(my) addr, then this device
	 * process peer's gon request and block to send gon req.
	 * if not (sa addr > da addr),
	 * this device will process gon request and drop gon req of peer.
	 */
	ifp = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vif->ifp;
	if (memcmp(mac, ifp->mac_addr, ETH_ALEN) < 0) {
		brcmf_dbg(INFO, "Block transmit gon req !!!\n");
		p2p->block_gon_req_tx = true;
		/* if we are finding a common channel for sending af,
		 * do not scan more to block to send current gon req
		 */
		if (test_and_clear_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL,
				       &p2p->status))
			complete(&p2p->afx_hdl.act_frm_scan);
		if (test_and_clear_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME,
				       &p2p->status))
			brcmf_p2p_stop_wait_next_action_frame(cfg);
		return false;
	}

	/* drop gon request of peer to process gon request by this device. */
	brcmf_dbg(INFO, "Drop received gon req !!!\n");

	return true;
}