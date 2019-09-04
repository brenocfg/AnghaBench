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
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  ccu_base; int /*<<< orphan*/  dxe_base; int /*<<< orphan*/  smd_channel; int /*<<< orphan*/  tx_rings_empty_state; int /*<<< orphan*/  tx_enable_state; int /*<<< orphan*/  nv; } ;
struct platform_device {int dummy; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCN36XX_DBG_MAC ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct ieee80211_hw* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  qcom_smem_state_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpmsg_destroy_ept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wcn36xx_remove(struct platform_device *pdev)
{
	struct ieee80211_hw *hw = platform_get_drvdata(pdev);
	struct wcn36xx *wcn = hw->priv;
	wcn36xx_dbg(WCN36XX_DBG_MAC, "platform remove\n");

	release_firmware(wcn->nv);

	ieee80211_unregister_hw(hw);

	qcom_smem_state_put(wcn->tx_enable_state);
	qcom_smem_state_put(wcn->tx_rings_empty_state);

	rpmsg_destroy_ept(wcn->smd_channel);

	iounmap(wcn->dxe_base);
	iounmap(wcn->ccu_base);

	mutex_destroy(&wcn->hal_mutex);
	ieee80211_free_hw(hw);

	return 0;
}