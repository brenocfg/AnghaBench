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
struct wcn36xx {int /*<<< orphan*/  conf_mutex; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCN36XX_DBG_MAC ; 
 int /*<<< orphan*/  WCN36XX_HAL_CFG_RTS_THRESHOLD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_smd_update_cfg (struct wcn36xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wcn36xx_set_rts_threshold(struct ieee80211_hw *hw, u32 value)
{
	struct wcn36xx *wcn = hw->priv;
	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac set RTS threshold %d\n", value);

	mutex_lock(&wcn->conf_mutex);
	wcn36xx_smd_update_cfg(wcn, WCN36XX_HAL_CFG_RTS_THRESHOLD, value);
	mutex_unlock(&wcn->conf_mutex);

	return 0;
}