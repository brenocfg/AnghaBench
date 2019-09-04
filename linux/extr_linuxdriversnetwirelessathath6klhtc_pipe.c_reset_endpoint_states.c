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
struct htc_target {struct htc_endpoint* endpoint; } ;
struct TYPE_2__ {int tx_credit_flow_enabled; int /*<<< orphan*/  tx_lookup_queue; } ;
struct htc_endpoint {int eid; TYPE_1__ pipe; struct htc_target* target; int /*<<< orphan*/  rx_bufq; int /*<<< orphan*/  txq; scalar_t__ max_txq_depth; scalar_t__ len_max; scalar_t__ svc_id; } ;

/* Variables and functions */
 int ENDPOINT_0 ; 
 int ENDPOINT_MAX ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_endpoint_states(struct htc_target *target)
{
	struct htc_endpoint *ep;
	int i;

	for (i = ENDPOINT_0; i < ENDPOINT_MAX; i++) {
		ep = &target->endpoint[i];
		ep->svc_id = 0;
		ep->len_max = 0;
		ep->max_txq_depth = 0;
		ep->eid = i;
		INIT_LIST_HEAD(&ep->txq);
		INIT_LIST_HEAD(&ep->pipe.tx_lookup_queue);
		INIT_LIST_HEAD(&ep->rx_bufq);
		ep->target = target;
		ep->pipe.tx_credit_flow_enabled = true;
	}
}