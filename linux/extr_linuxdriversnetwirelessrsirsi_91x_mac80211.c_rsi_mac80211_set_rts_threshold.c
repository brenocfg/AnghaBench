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
struct rsi_hw {struct rsi_common* priv; } ;
struct rsi_common {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rts_threshold; } ;
struct ieee80211_hw {struct rsi_hw* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsi_mac80211_set_rts_threshold(struct ieee80211_hw *hw,
					  u32 value)
{
	struct rsi_hw *adapter = hw->priv;
	struct rsi_common *common = adapter->priv;

	mutex_lock(&common->mutex);
	common->rts_threshold = value;
	mutex_unlock(&common->mutex);

	return 0;
}