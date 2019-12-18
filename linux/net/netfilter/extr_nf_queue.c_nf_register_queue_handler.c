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
struct nf_queue_handler {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_handler; } ;
struct net {TYPE_1__ nf; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nf_queue_handler const*) ; 

void nf_register_queue_handler(struct net *net, const struct nf_queue_handler *qh)
{
	/* should never happen, we only have one queueing backend in kernel */
	WARN_ON(rcu_access_pointer(net->nf.queue_handler));
	rcu_assign_pointer(net->nf.queue_handler, qh);
}