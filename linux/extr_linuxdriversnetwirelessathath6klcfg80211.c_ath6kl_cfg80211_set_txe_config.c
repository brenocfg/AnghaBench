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
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct ath6kl_vif {scalar_t__ nw_type; scalar_t__ sme_state; int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  txe_intvl; } ;
struct ath6kl {int /*<<< orphan*/  wmi; int /*<<< orphan*/  fw_capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_TX_ERR_NOTIFY ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 scalar_t__ INFRA_NETWORK ; 
 scalar_t__ SME_CONNECTED ; 
 struct ath6kl* ath6kl_priv (struct net_device*) ; 
 int ath6kl_wmi_set_txe_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_cfg80211_set_txe_config(struct wiphy *wiphy,
					  struct net_device *dev,
					  u32 rate, u32 pkts, u32 intvl)
{
	struct ath6kl *ar = ath6kl_priv(dev);
	struct ath6kl_vif *vif = netdev_priv(dev);

	if (vif->nw_type != INFRA_NETWORK ||
	    !test_bit(ATH6KL_FW_CAPABILITY_TX_ERR_NOTIFY, ar->fw_capabilities))
		return -EOPNOTSUPP;

	if (vif->sme_state != SME_CONNECTED)
		return -ENOTCONN;

	/* save this since the firmware won't report the interval */
	vif->txe_intvl = intvl;

	return ath6kl_wmi_set_txe_notify(ar->wmi, vif->fw_vif_idx,
					 rate, pkts, intvl);
}