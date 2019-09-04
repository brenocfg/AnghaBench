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
struct ath6kl_vif {int dummy; } ;
struct aggr_info_conn {int dummy; } ;
struct aggr_info {int /*<<< orphan*/  rx_amsdu_freeq; void* aggr_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGGR_NUM_OF_FREE_NETBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  aggr_conn_init (struct ath6kl_vif*,struct aggr_info*,void*) ; 
 int /*<<< orphan*/  ath6kl_alloc_netbufs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int /*<<< orphan*/  kfree (struct aggr_info*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

struct aggr_info *aggr_init(struct ath6kl_vif *vif)
{
	struct aggr_info *p_aggr = NULL;

	p_aggr = kzalloc(sizeof(struct aggr_info), GFP_KERNEL);
	if (!p_aggr) {
		ath6kl_err("failed to alloc memory for aggr_node\n");
		return NULL;
	}

	p_aggr->aggr_conn = kzalloc(sizeof(struct aggr_info_conn), GFP_KERNEL);
	if (!p_aggr->aggr_conn) {
		ath6kl_err("failed to alloc memory for connection specific aggr info\n");
		kfree(p_aggr);
		return NULL;
	}

	aggr_conn_init(vif, p_aggr, p_aggr->aggr_conn);

	skb_queue_head_init(&p_aggr->rx_amsdu_freeq);
	ath6kl_alloc_netbufs(&p_aggr->rx_amsdu_freeq, AGGR_NUM_OF_FREE_NETBUFS);

	return p_aggr;
}