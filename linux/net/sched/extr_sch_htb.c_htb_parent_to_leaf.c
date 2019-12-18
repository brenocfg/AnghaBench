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
struct htb_sched {TYPE_1__* hlevel; } ;
struct TYPE_4__ {struct Qdisc* q; } ;
struct htb_class {size_t level; scalar_t__ cmode; int /*<<< orphan*/  t_c; int /*<<< orphan*/  cbuffer; int /*<<< orphan*/  ctokens; int /*<<< orphan*/  buffer; int /*<<< orphan*/  tokens; TYPE_2__ leaf; int /*<<< orphan*/  inner; int /*<<< orphan*/  pq_node; scalar_t__ prio_activity; struct htb_class* parent; } ;
struct Qdisc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  wait_pq; } ;

/* Variables and functions */
 scalar_t__ HTB_CAN_SEND ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  htb_safe_rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct Qdisc noop_qdisc ; 

__attribute__((used)) static void htb_parent_to_leaf(struct htb_sched *q, struct htb_class *cl,
			       struct Qdisc *new_q)
{
	struct htb_class *parent = cl->parent;

	WARN_ON(cl->level || !cl->leaf.q || cl->prio_activity);

	if (parent->cmode != HTB_CAN_SEND)
		htb_safe_rb_erase(&parent->pq_node,
				  &q->hlevel[parent->level].wait_pq);

	parent->level = 0;
	memset(&parent->inner, 0, sizeof(parent->inner));
	parent->leaf.q = new_q ? new_q : &noop_qdisc;
	parent->tokens = parent->buffer;
	parent->ctokens = parent->cbuffer;
	parent->t_c = ktime_get_ns();
	parent->cmode = HTB_CAN_SEND;
}