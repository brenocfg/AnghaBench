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
struct sock {int /*<<< orphan*/  sk_reuseport_cb; } ;
struct sctp_hashbucket {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;
struct sctp_ep_common {size_t hashent; int /*<<< orphan*/  node; TYPE_1__ bind_addr; struct sock* sk; } ;
struct sctp_endpoint {struct sctp_ep_common base; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reuseport_detach_sock (struct sock*) ; 
 size_t sctp_ep_hashfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_hashbucket* sctp_ep_hashtable ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __sctp_unhash_endpoint(struct sctp_endpoint *ep)
{
	struct sock *sk = ep->base.sk;
	struct sctp_hashbucket *head;
	struct sctp_ep_common *epb;

	epb = &ep->base;

	epb->hashent = sctp_ep_hashfn(sock_net(sk), epb->bind_addr.port);

	head = &sctp_ep_hashtable[epb->hashent];

	if (rcu_access_pointer(sk->sk_reuseport_cb))
		reuseport_detach_sock(sk);

	write_lock(&head->lock);
	hlist_del_init(&epb->node);
	write_unlock(&head->lock);
}