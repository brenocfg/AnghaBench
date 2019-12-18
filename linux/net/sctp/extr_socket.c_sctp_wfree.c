#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_wmem_queued; } ;
struct sk_buff {scalar_t__ truesize; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_shared_key {int /*<<< orphan*/  key_id; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  key_list; scalar_t__ deactivated; } ;
struct sctp_chunk {struct sctp_shared_key* shkey; struct sctp_association* asoc; } ;
struct TYPE_7__ {TYPE_2__* si; } ;
struct TYPE_5__ {struct sock* sk; } ;
struct sctp_association {int /*<<< orphan*/  ulpq; TYPE_3__ stream; int /*<<< orphan*/  sndbuf_used; TYPE_1__ base; } ;
struct TYPE_8__ {struct sctp_chunk* destructor_arg; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* enqueue_event ) (int /*<<< orphan*/ *,struct sctp_ulpevent*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCTP_AUTH_FREE_KEY ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_sub_and_test (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_association_put (struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_auth_shkey_release (struct sctp_shared_key*) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_authkey (struct sctp_association*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_wake_up_waiters (struct sock*,struct sctp_association*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,scalar_t__) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_wfree (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct sctp_ulpevent*) ; 

__attribute__((used)) static void sctp_wfree(struct sk_buff *skb)
{
	struct sctp_chunk *chunk = skb_shinfo(skb)->destructor_arg;
	struct sctp_association *asoc = chunk->asoc;
	struct sock *sk = asoc->base.sk;

	sk_mem_uncharge(sk, skb->truesize);
	sk->sk_wmem_queued -= skb->truesize + sizeof(struct sctp_chunk);
	asoc->sndbuf_used -= skb->truesize + sizeof(struct sctp_chunk);
	WARN_ON(refcount_sub_and_test(sizeof(struct sctp_chunk),
				      &sk->sk_wmem_alloc));

	if (chunk->shkey) {
		struct sctp_shared_key *shkey = chunk->shkey;

		/* refcnt == 2 and !list_empty mean after this release, it's
		 * not being used anywhere, and it's time to notify userland
		 * that this shkey can be freed if it's been deactivated.
		 */
		if (shkey->deactivated && !list_empty(&shkey->key_list) &&
		    refcount_read(&shkey->refcnt) == 2) {
			struct sctp_ulpevent *ev;

			ev = sctp_ulpevent_make_authkey(asoc, shkey->key_id,
							SCTP_AUTH_FREE_KEY,
							GFP_KERNEL);
			if (ev)
				asoc->stream.si->enqueue_event(&asoc->ulpq, ev);
		}
		sctp_auth_shkey_release(chunk->shkey);
	}

	sock_wfree(skb);
	sctp_wake_up_waiters(sk, asoc);

	sctp_association_put(asoc);
}