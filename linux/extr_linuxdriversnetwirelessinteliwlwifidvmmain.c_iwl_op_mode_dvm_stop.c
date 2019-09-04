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
struct iwl_priv {int /*<<< orphan*/  hw; int /*<<< orphan*/  trans; int /*<<< orphan*/  beacon_skb; int /*<<< orphan*/ * workqueue; int /*<<< orphan*/  nvm_data; int /*<<< orphan*/  eeprom_blob; } ;
struct iwl_op_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_OP_MODE_GET_DVM (struct iwl_op_mode*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_op_mode_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_tt_exit (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_uninit_drv (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwlagn_mac_unregister (struct iwl_priv*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_op_mode_dvm_stop(struct iwl_op_mode *op_mode)
{
	struct iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);

	IWL_DEBUG_INFO(priv, "*** UNLOAD DRIVER ***\n");

	iwlagn_mac_unregister(priv);

	iwl_tt_exit(priv);

	kfree(priv->eeprom_blob);
	kfree(priv->nvm_data);

	/*netif_stop_queue(dev); */
	flush_workqueue(priv->workqueue);

	/* ieee80211_unregister_hw calls iwlagn_mac_stop, which flushes
	 * priv->workqueue... so we can't take down the workqueue
	 * until now... */
	destroy_workqueue(priv->workqueue);
	priv->workqueue = NULL;

	iwl_uninit_drv(priv);

	dev_kfree_skb(priv->beacon_skb);

	iwl_trans_op_mode_leave(priv->trans);
	ieee80211_free_hw(priv->hw);
}