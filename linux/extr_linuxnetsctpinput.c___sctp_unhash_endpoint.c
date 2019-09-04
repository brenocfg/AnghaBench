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
struct sctp_hashbucket {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;
struct sctp_ep_common {size_t hashent; int /*<<< orphan*/  node; TYPE_1__ bind_addr; int /*<<< orphan*/  sk; } ;
struct sctp_endpoint {struct sctp_ep_common base; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 size_t sctp_ep_hashfn (struct net*,int /*<<< orphan*/ ) ; 
 struct sctp_hashbucket* sctp_ep_hashtable ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __sctp_unhash_endpoint(struct sctp_endpoint *ep)
{
	struct net *net = sock_net(ep->base.sk);
	struct sctp_hashbucket *head;
	struct sctp_ep_common *epb;

	epb = &ep->base;

	epb->hashent = sctp_ep_hashfn(net, epb->bind_addr.port);

	head = &sctp_ep_hashtable[epb->hashent];

	write_lock(&head->lock);
	hlist_del_init(&epb->node);
	write_unlock(&head->lock);
}