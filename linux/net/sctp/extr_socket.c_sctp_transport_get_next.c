#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sctp_transport {TYPE_3__* asoc; } ;
struct rhashtable_iter {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_5__ {struct sctp_transport* primary_path; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk; } ;
struct TYPE_6__ {TYPE_2__ peer; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ IS_ERR (struct sctp_transport*) ; 
 int /*<<< orphan*/  PTR_ERR (struct sctp_transport*) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 struct sctp_transport* rhashtable_walk_next (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  sctp_transport_hold (struct sctp_transport*) ; 
 int /*<<< orphan*/  sctp_transport_put (struct sctp_transport*) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

struct sctp_transport *sctp_transport_get_next(struct net *net,
					       struct rhashtable_iter *iter)
{
	struct sctp_transport *t;

	t = rhashtable_walk_next(iter);
	for (; t; t = rhashtable_walk_next(iter)) {
		if (IS_ERR(t)) {
			if (PTR_ERR(t) == -EAGAIN)
				continue;
			break;
		}

		if (!sctp_transport_hold(t))
			continue;

		if (net_eq(sock_net(t->asoc->base.sk), net) &&
		    t->asoc->peer.primary_path == t)
			break;

		sctp_transport_put(t);
	}

	return t;
}