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
typedef  int /*<<< orphan*/  u16 ;
struct htc_target {struct htc_endpoint* endpoint; } ;
struct htc_endpoint {scalar_t__ svc_id; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  htc_flush_tx_endpoint (struct htc_target*,struct htc_endpoint*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath6kl_htc_pipe_flush_txep(struct htc_target *target,
				       enum htc_endpoint_id endpoint, u16 tag)
{
	struct htc_endpoint *ep = &target->endpoint[endpoint];

	if (ep->svc_id == 0) {
		WARN_ON_ONCE(1);
		/* not in use.. */
		return;
	}

	htc_flush_tx_endpoint(target, ep, tag);
}