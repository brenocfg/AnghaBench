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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wmi_txe_notify_event {int /*<<< orphan*/  pkts; int /*<<< orphan*/  rate; } ;
struct wmi {int dummy; } ;
struct ath6kl_vif {scalar_t__ nw_type; scalar_t__ sme_state; int /*<<< orphan*/  txe_intvl; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ndev; TYPE_1__* ar; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_TX_ERR_NOTIFY ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ INFRA_NETWORK ; 
 scalar_t__ SME_CONNECTED ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_cqm_txe_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_txe_notify_event_rx(struct wmi *wmi, u8 *datap, int len,
					  struct ath6kl_vif *vif)
{
	struct wmi_txe_notify_event *ev;
	u32 rate, pkts;

	if (len < sizeof(*ev))
		return -EINVAL;

	if (vif->nw_type != INFRA_NETWORK ||
	    !test_bit(ATH6KL_FW_CAPABILITY_TX_ERR_NOTIFY,
		      vif->ar->fw_capabilities))
		return -EOPNOTSUPP;

	if (vif->sme_state != SME_CONNECTED)
		return -ENOTCONN;

	ev = (struct wmi_txe_notify_event *) datap;
	rate = le32_to_cpu(ev->rate);
	pkts = le32_to_cpu(ev->pkts);

	ath6kl_dbg(ATH6KL_DBG_WMI, "TXE notify event: peer %pM rate %d%% pkts %d intvl %ds\n",
		   vif->bssid, rate, pkts, vif->txe_intvl);

	cfg80211_cqm_txe_notify(vif->ndev, vif->bssid, pkts,
				rate, vif->txe_intvl, GFP_KERNEL);

	return 0;
}