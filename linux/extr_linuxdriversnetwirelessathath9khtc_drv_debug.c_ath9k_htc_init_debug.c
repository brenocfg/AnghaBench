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
struct ath_hw {int dummy; } ;
struct ath_common {scalar_t__ priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  debugfs_phy; int /*<<< orphan*/  rx_stats; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  ah; TYPE_3__ debug; int /*<<< orphan*/  spec_priv; TYPE_2__* hw; } ;
struct TYPE_5__ {TYPE_1__* wiphy; } ;
struct TYPE_4__ {int /*<<< orphan*/  debugfsdir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  ath9k_cmn_debug_base_eeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_cmn_debug_modal_eeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_cmn_debug_phy_err (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_cmn_debug_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_cmn_spectral_init_debug (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct ath9k_htc_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_debug ; 
 int /*<<< orphan*/  fops_queue ; 
 int /*<<< orphan*/  fops_skb_rx ; 
 int /*<<< orphan*/  fops_slot ; 
 int /*<<< orphan*/  fops_tgt_int_stats ; 
 int /*<<< orphan*/  fops_tgt_rx_stats ; 
 int /*<<< orphan*/  fops_tgt_tx_stats ; 
 int /*<<< orphan*/  fops_xmit ; 

int ath9k_htc_init_debug(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_htc_priv *priv = (struct ath9k_htc_priv *) common->priv;

	priv->debug.debugfs_phy = debugfs_create_dir(KBUILD_MODNAME,
					     priv->hw->wiphy->debugfsdir);
	if (!priv->debug.debugfs_phy)
		return -ENOMEM;

	ath9k_cmn_spectral_init_debug(&priv->spec_priv, priv->debug.debugfs_phy);

	debugfs_create_file("tgt_int_stats", 0400, priv->debug.debugfs_phy,
			    priv, &fops_tgt_int_stats);
	debugfs_create_file("tgt_tx_stats", 0400, priv->debug.debugfs_phy,
			    priv, &fops_tgt_tx_stats);
	debugfs_create_file("tgt_rx_stats", 0400, priv->debug.debugfs_phy,
			    priv, &fops_tgt_rx_stats);
	debugfs_create_file("xmit", 0400, priv->debug.debugfs_phy,
			    priv, &fops_xmit);
	debugfs_create_file("skb_rx", 0400, priv->debug.debugfs_phy,
			    priv, &fops_skb_rx);

	ath9k_cmn_debug_recv(priv->debug.debugfs_phy, &priv->debug.rx_stats);
	ath9k_cmn_debug_phy_err(priv->debug.debugfs_phy, &priv->debug.rx_stats);

	debugfs_create_file("slot", 0400, priv->debug.debugfs_phy,
			    priv, &fops_slot);
	debugfs_create_file("queue", 0400, priv->debug.debugfs_phy,
			    priv, &fops_queue);
	debugfs_create_file("debug", 0600, priv->debug.debugfs_phy,
			    priv, &fops_debug);

	ath9k_cmn_debug_base_eeprom(priv->debug.debugfs_phy, priv->ah);
	ath9k_cmn_debug_modal_eeprom(priv->debug.debugfs_phy, priv->ah);

	return 0;
}