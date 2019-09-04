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
typedef  size_t u8 ;
struct sk_buff {size_t* data; } ;
struct htc_target {struct htc_endpoint* endpoint; } ;
struct htc_packet {scalar_t__ status; } ;
struct htc_frame_hdr {size_t eid; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_credit_flow_enabled; } ;
struct htc_endpoint {TYPE_1__ pipe; } ;
struct ath6kl {struct htc_target* htc_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 struct htc_packet* htc_lookup_tx_packet (struct htc_target*,struct htc_endpoint*,struct sk_buff*) ; 
 int /*<<< orphan*/  htc_try_send (struct htc_target*,struct htc_endpoint*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_packet_completion (struct htc_target*,struct htc_packet*) ; 

__attribute__((used)) static int ath6kl_htc_pipe_tx_complete(struct ath6kl *ar, struct sk_buff *skb)
{
	struct htc_target *target = ar->htc_target;
	struct htc_frame_hdr *htc_hdr;
	struct htc_endpoint *ep;
	struct htc_packet *packet;
	u8 ep_id, *netdata;

	netdata = skb->data;

	htc_hdr = (struct htc_frame_hdr *) netdata;

	ep_id = htc_hdr->eid;
	ep = &target->endpoint[ep_id];

	packet = htc_lookup_tx_packet(target, ep, skb);
	if (packet == NULL) {
		/* may have already been flushed and freed */
		ath6kl_err("HTC TX lookup failed!\n");
	} else {
		/* will be giving this buffer back to upper layers */
		packet->status = 0;
		send_packet_completion(target, packet);
	}
	skb = NULL;

	if (!ep->pipe.tx_credit_flow_enabled) {
		/*
		 * note: when using TX credit flow, the re-checking of queues
		 * happens when credits flow back from the target. in the
		 * non-TX credit case, we recheck after the packet completes
		 */
		htc_try_send(target, ep, NULL);
	}

	return 0;
}