#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sctp_ulpq {struct sctp_association* asoc; } ;
struct sctp_data_chunk {int dummy; } ;
struct sctp_chunk {int /*<<< orphan*/  skb; TYPE_1__* chunk_hdr; } ;
struct TYPE_6__ {TYPE_3__* sk; } ;
struct sctp_association {TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ __u32 ;
typedef  scalar_t__ __u16 ;
struct TYPE_7__ {int /*<<< orphan*/  sk_receive_queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpq_partial_delivery (struct sctp_ulpq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpq_reasm_drain (struct sctp_ulpq*) ; 
 scalar_t__ sctp_ulpq_renege_frags (struct sctp_ulpq*,scalar_t__) ; 
 scalar_t__ sctp_ulpq_renege_order (struct sctp_ulpq*,scalar_t__) ; 
 int sctp_ulpq_tail_data (struct sctp_ulpq*,struct sctp_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_mem_reclaim (TYPE_3__*) ; 
 scalar_t__ sk_rmem_schedule (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 

void sctp_ulpq_renege(struct sctp_ulpq *ulpq, struct sctp_chunk *chunk,
		      gfp_t gfp)
{
	struct sctp_association *asoc = ulpq->asoc;
	__u32 freed = 0;
	__u16 needed;

	needed = ntohs(chunk->chunk_hdr->length) -
		 sizeof(struct sctp_data_chunk);

	if (skb_queue_empty(&asoc->base.sk->sk_receive_queue)) {
		freed = sctp_ulpq_renege_order(ulpq, needed);
		if (freed < needed)
			freed += sctp_ulpq_renege_frags(ulpq, needed - freed);
	}
	/* If able to free enough room, accept this chunk. */
	if (sk_rmem_schedule(asoc->base.sk, chunk->skb, needed) &&
	    freed >= needed) {
		int retval = sctp_ulpq_tail_data(ulpq, chunk, gfp);
		/*
		 * Enter partial delivery if chunk has not been
		 * delivered; otherwise, drain the reassembly queue.
		 */
		if (retval <= 0)
			sctp_ulpq_partial_delivery(ulpq, gfp);
		else if (retval == 1)
			sctp_ulpq_reasm_drain(ulpq);
	}

	sk_mem_reclaim(asoc->base.sk);
}