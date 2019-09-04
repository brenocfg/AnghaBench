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
typedef  void* u8 ;
struct iwl_priv {int bt_full_concurrent; int bt_is_sco; int /*<<< orphan*/  agg_q_alloc; int /*<<< orphan*/ * queue_stop_count; int /*<<< orphan*/ * queue_to_mac80211; void* bt_status; void* bt_traffic_load; void* bt_ci_compliance; scalar_t__ is_open; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int IWLAGN_FIRST_AMPDU_QUEUE ; 
 int /*<<< orphan*/  IWL_INVALID_MAC80211_QUEUE ; 
 int IWL_MAX_HW_QUEUES ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_down (struct iwl_priv*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void iwlagn_prepare_restart(struct iwl_priv *priv)
{
	bool bt_full_concurrent;
	u8 bt_ci_compliance;
	u8 bt_load;
	u8 bt_status;
	bool bt_is_sco;
	int i;

	lockdep_assert_held(&priv->mutex);

	priv->is_open = 0;

	/*
	 * __iwl_down() will clear the BT status variables,
	 * which is correct, but when we restart we really
	 * want to keep them so restore them afterwards.
	 *
	 * The restart process will later pick them up and
	 * re-configure the hw when we reconfigure the BT
	 * command.
	 */
	bt_full_concurrent = priv->bt_full_concurrent;
	bt_ci_compliance = priv->bt_ci_compliance;
	bt_load = priv->bt_traffic_load;
	bt_status = priv->bt_status;
	bt_is_sco = priv->bt_is_sco;

	iwl_down(priv);

	priv->bt_full_concurrent = bt_full_concurrent;
	priv->bt_ci_compliance = bt_ci_compliance;
	priv->bt_traffic_load = bt_load;
	priv->bt_status = bt_status;
	priv->bt_is_sco = bt_is_sco;

	/* reset aggregation queues */
	for (i = IWLAGN_FIRST_AMPDU_QUEUE; i < IWL_MAX_HW_QUEUES; i++)
		priv->queue_to_mac80211[i] = IWL_INVALID_MAC80211_QUEUE;
	/* and stop counts */
	for (i = 0; i < IWL_MAX_HW_QUEUES; i++)
		atomic_set(&priv->queue_stop_count[i], 0);

	memset(priv->agg_q_alloc, 0, sizeof(priv->agg_q_alloc));
}