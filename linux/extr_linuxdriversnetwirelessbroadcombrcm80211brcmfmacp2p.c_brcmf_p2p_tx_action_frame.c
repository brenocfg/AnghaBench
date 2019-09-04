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
struct brcmf_p2p_info {int /*<<< orphan*/  status; int /*<<< orphan*/  send_af_done; int /*<<< orphan*/  af_tx_sent_jiffies; int /*<<< orphan*/  af_sent_channel; TYPE_1__* bss_idx; } ;
struct brcmf_fil_af_params_le {int /*<<< orphan*/  channel; } ;
struct brcmf_cfg80211_vif {int /*<<< orphan*/  ifp; } ;
typedef  int s32 ;
struct TYPE_2__ {struct brcmf_cfg80211_vif* vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_P2P_STATUS_ACTION_TX_COMPLETED ; 
 int /*<<< orphan*/  BRCMF_P2P_STATUS_ACTION_TX_NOACK ; 
 int EIO ; 
 size_t P2PAPI_BSSCFG_DEVICE ; 
 int /*<<< orphan*/  P2P_AF_MAX_WAIT_TIME ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int brcmf_fil_bsscfg_data_set (int /*<<< orphan*/ ,char*,struct brcmf_fil_af_params_le*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 brcmf_p2p_tx_action_frame(struct brcmf_p2p_info *p2p,
				     struct brcmf_fil_af_params_le *af_params)
{
	struct brcmf_cfg80211_vif *vif;
	s32 err = 0;
	s32 timeout = 0;

	brcmf_dbg(TRACE, "Enter\n");

	reinit_completion(&p2p->send_af_done);
	clear_bit(BRCMF_P2P_STATUS_ACTION_TX_COMPLETED, &p2p->status);
	clear_bit(BRCMF_P2P_STATUS_ACTION_TX_NOACK, &p2p->status);

	vif = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vif;
	err = brcmf_fil_bsscfg_data_set(vif->ifp, "actframe", af_params,
					sizeof(*af_params));
	if (err) {
		brcmf_err(" sending action frame has failed\n");
		goto exit;
	}

	p2p->af_sent_channel = le32_to_cpu(af_params->channel);
	p2p->af_tx_sent_jiffies = jiffies;

	timeout = wait_for_completion_timeout(&p2p->send_af_done,
					      P2P_AF_MAX_WAIT_TIME);

	if (test_bit(BRCMF_P2P_STATUS_ACTION_TX_COMPLETED, &p2p->status)) {
		brcmf_dbg(TRACE, "TX action frame operation is success\n");
	} else {
		err = -EIO;
		brcmf_dbg(TRACE, "TX action frame operation has failed\n");
	}
	/* clear status bit for action tx */
	clear_bit(BRCMF_P2P_STATUS_ACTION_TX_COMPLETED, &p2p->status);
	clear_bit(BRCMF_P2P_STATUS_ACTION_TX_NOACK, &p2p->status);

exit:
	return err;
}