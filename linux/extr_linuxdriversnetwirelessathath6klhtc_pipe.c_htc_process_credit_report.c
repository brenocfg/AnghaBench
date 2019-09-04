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
struct htc_target {int /*<<< orphan*/  tx_lock; struct htc_endpoint* endpoint; } ;
struct TYPE_2__ {scalar_t__ credits; } ;
struct htc_endpoint {int /*<<< orphan*/  txq; TYPE_1__ cred_dist; } ;
struct htc_credit_report {size_t eid; scalar_t__ credits; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 size_t ENDPOINT_MAX ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ get_queue_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htc_try_send (struct htc_target*,struct htc_endpoint*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void htc_process_credit_report(struct htc_target *target,
				      struct htc_credit_report *rpt,
				      int num_entries,
				      enum htc_endpoint_id from_ep)
{
	int total_credits = 0, i;
	struct htc_endpoint *ep;

	/* lock out TX while we update credits */
	spin_lock_bh(&target->tx_lock);

	for (i = 0; i < num_entries; i++, rpt++) {
		if (rpt->eid >= ENDPOINT_MAX) {
			WARN_ON_ONCE(1);
			spin_unlock_bh(&target->tx_lock);
			return;
		}

		ep = &target->endpoint[rpt->eid];
		ep->cred_dist.credits += rpt->credits;

		if (ep->cred_dist.credits && get_queue_depth(&ep->txq)) {
			spin_unlock_bh(&target->tx_lock);
			htc_try_send(target, ep, NULL);
			spin_lock_bh(&target->tx_lock);
		}

		total_credits += rpt->credits;
	}
	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "Report indicated %d credits to distribute\n",
		   total_credits);

	spin_unlock_bh(&target->tx_lock);
}