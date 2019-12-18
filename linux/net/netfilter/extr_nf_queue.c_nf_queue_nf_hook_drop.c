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
struct nf_queue_handler {int /*<<< orphan*/  (* nf_hook_drop ) (struct net*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  queue_handler; } ;
struct net {TYPE_1__ nf; } ;

/* Variables and functions */
 struct nf_queue_handler* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct net*) ; 

void nf_queue_nf_hook_drop(struct net *net)
{
	const struct nf_queue_handler *qh;

	rcu_read_lock();
	qh = rcu_dereference(net->nf.queue_handler);
	if (qh)
		qh->nf_hook_drop(net);
	rcu_read_unlock();
}