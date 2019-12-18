#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct tipc_bclink_entry {TYPE_1__ inputq2; int /*<<< orphan*/  arrvq; TYPE_2__ inputq1; } ;
struct tipc_node {int /*<<< orphan*/  net; struct tipc_bclink_entry bc_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_splice_tail_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_sk_mcast_rcv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void tipc_node_mcast_rcv(struct tipc_node *n)
{
	struct tipc_bclink_entry *be = &n->bc_entry;

	/* 'arrvq' is under inputq2's lock protection */
	spin_lock_bh(&be->inputq2.lock);
	spin_lock_bh(&be->inputq1.lock);
	skb_queue_splice_tail_init(&be->inputq1, &be->arrvq);
	spin_unlock_bh(&be->inputq1.lock);
	spin_unlock_bh(&be->inputq2.lock);
	tipc_sk_mcast_rcv(n->net, &be->arrvq, &be->inputq2);
}