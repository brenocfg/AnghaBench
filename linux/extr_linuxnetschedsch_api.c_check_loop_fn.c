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
struct qdisc_walker {int dummy; } ;
struct check_loop_arg {int depth; struct Qdisc* p; } ;
struct Qdisc_class_ops {struct Qdisc* (* leaf ) (struct Qdisc*,unsigned long) ;} ;
struct Qdisc {TYPE_1__* ops; } ;
struct TYPE_2__ {struct Qdisc_class_ops* cl_ops; } ;

/* Variables and functions */
 int ELOOP ; 
 int check_loop (struct Qdisc*,struct Qdisc*,int) ; 
 struct Qdisc* stub1 (struct Qdisc*,unsigned long) ; 

__attribute__((used)) static int
check_loop_fn(struct Qdisc *q, unsigned long cl, struct qdisc_walker *w)
{
	struct Qdisc *leaf;
	const struct Qdisc_class_ops *cops = q->ops->cl_ops;
	struct check_loop_arg *arg = (struct check_loop_arg *)w;

	leaf = cops->leaf(q, cl);
	if (leaf) {
		if (leaf == arg->p || arg->depth > 7)
			return -ELOOP;
		return check_loop(leaf, arg->p, arg->depth + 1);
	}
	return 0;
}