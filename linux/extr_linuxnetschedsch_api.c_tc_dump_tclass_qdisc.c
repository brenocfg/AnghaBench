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
struct tcmsg {scalar_t__ tcm_parent; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ stop; scalar_t__ count; scalar_t__ skip; int /*<<< orphan*/  fn; } ;
struct qdisc_dump_args {TYPE_3__ w; struct netlink_callback* cb; struct sk_buff* skb; } ;
struct netlink_callback {scalar_t__* args; } ;
struct Qdisc {scalar_t__ handle; TYPE_2__* ops; } ;
struct TYPE_5__ {TYPE_1__* cl_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* walk ) (struct Qdisc*,TYPE_3__*) ;} ;

/* Variables and functions */
 scalar_t__ TC_H_MAJ (scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qdisc_class_dump ; 
 int /*<<< orphan*/  stub1 (struct Qdisc*,TYPE_3__*) ; 
 scalar_t__ tc_qdisc_dump_ignore (struct Qdisc*,int) ; 

__attribute__((used)) static int tc_dump_tclass_qdisc(struct Qdisc *q, struct sk_buff *skb,
				struct tcmsg *tcm, struct netlink_callback *cb,
				int *t_p, int s_t)
{
	struct qdisc_dump_args arg;

	if (tc_qdisc_dump_ignore(q, false) ||
	    *t_p < s_t || !q->ops->cl_ops ||
	    (tcm->tcm_parent &&
	     TC_H_MAJ(tcm->tcm_parent) != q->handle)) {
		(*t_p)++;
		return 0;
	}
	if (*t_p > s_t)
		memset(&cb->args[1], 0, sizeof(cb->args)-sizeof(cb->args[0]));
	arg.w.fn = qdisc_class_dump;
	arg.skb = skb;
	arg.cb = cb;
	arg.w.stop  = 0;
	arg.w.skip = cb->args[1];
	arg.w.count = 0;
	q->ops->cl_ops->walk(q, &arg.w);
	cb->args[1] = arg.w.count;
	if (arg.w.stop)
		return -1;
	(*t_p)++;
	return 0;
}