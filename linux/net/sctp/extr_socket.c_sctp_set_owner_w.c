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
struct sock {int /*<<< orphan*/  sk_wmem_queued; int /*<<< orphan*/  sk_wmem_alloc; } ;
struct sctp_chunk {TYPE_3__* skb; scalar_t__ shkey; struct sctp_association* asoc; } ;
struct TYPE_5__ {struct sock* sk; } ;
struct sctp_association {int /*<<< orphan*/  sndbuf_used; TYPE_1__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  truesize; int /*<<< orphan*/  destructor; } ;
struct TYPE_6__ {struct sctp_chunk* destructor_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_association_hold (struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_auth_shkey_hold (scalar_t__) ; 
 int /*<<< orphan*/  sctp_wfree ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_w (TYPE_3__*,struct sock*) ; 
 TYPE_2__* skb_shinfo (TYPE_3__*) ; 

__attribute__((used)) static inline void sctp_set_owner_w(struct sctp_chunk *chunk)
{
	struct sctp_association *asoc = chunk->asoc;
	struct sock *sk = asoc->base.sk;

	/* The sndbuf space is tracked per association.  */
	sctp_association_hold(asoc);

	if (chunk->shkey)
		sctp_auth_shkey_hold(chunk->shkey);

	skb_set_owner_w(chunk->skb, sk);

	chunk->skb->destructor = sctp_wfree;
	/* Save the chunk pointer in skb for sctp_wfree to use later.  */
	skb_shinfo(chunk->skb)->destructor_arg = chunk;

	refcount_add(sizeof(struct sctp_chunk), &sk->sk_wmem_alloc);
	asoc->sndbuf_used += chunk->skb->truesize + sizeof(struct sctp_chunk);
	sk->sk_wmem_queued += chunk->skb->truesize + sizeof(struct sctp_chunk);
	sk_mem_charge(sk, chunk->skb->truesize);
}