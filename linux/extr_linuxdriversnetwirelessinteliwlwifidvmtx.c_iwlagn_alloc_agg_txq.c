#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_priv {int* queue_to_mac80211; int /*<<< orphan*/  agg_q_alloc; TYPE_2__* cfg; } ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {int num_of_queues; } ;

/* Variables and functions */
 int ENOSPC ; 
 int IWLAGN_FIRST_AMPDU_QUEUE ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwlagn_alloc_agg_txq(struct iwl_priv *priv, int mq)
{
	int q;

	for (q = IWLAGN_FIRST_AMPDU_QUEUE;
	     q < priv->cfg->base_params->num_of_queues; q++) {
		if (!test_and_set_bit(q, priv->agg_q_alloc)) {
			priv->queue_to_mac80211[q] = mq;
			return q;
		}
	}

	return -ENOSPC;
}