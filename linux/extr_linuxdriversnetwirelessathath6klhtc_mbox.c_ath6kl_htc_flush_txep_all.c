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
struct htc_target {struct htc_endpoint* endpoint; } ;
struct htc_endpoint {scalar_t__ svc_id; } ;

/* Variables and functions */
 int ENDPOINT_0 ; 
 int ENDPOINT_MAX ; 
 int /*<<< orphan*/  HTC_TX_PACKET_TAG_ALL ; 
 int /*<<< orphan*/  ath6kl_htc_mbox_flush_txep (struct htc_target*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_cred_dist_stats (struct htc_target*) ; 

__attribute__((used)) static void ath6kl_htc_flush_txep_all(struct htc_target *target)
{
	struct htc_endpoint *endpoint;
	int i;

	dump_cred_dist_stats(target);

	for (i = ENDPOINT_0; i < ENDPOINT_MAX; i++) {
		endpoint = &target->endpoint[i];
		if (endpoint->svc_id == 0)
			/* not in use.. */
			continue;
		ath6kl_htc_mbox_flush_txep(target, i, HTC_TX_PACKET_TAG_ALL);
	}
}