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
struct TYPE_6__ {scalar_t__ stop; int /*<<< orphan*/  fn; scalar_t__ count; scalar_t__ skip; } ;
struct check_loop_arg {int depth; TYPE_3__ w; struct Qdisc* p; } ;
struct Qdisc {TYPE_2__* ops; } ;
struct TYPE_5__ {TYPE_1__* cl_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* walk ) (struct Qdisc*,TYPE_3__*) ;} ;

/* Variables and functions */
 int ELOOP ; 
 int /*<<< orphan*/  check_loop_fn ; 
 int /*<<< orphan*/  stub1 (struct Qdisc*,TYPE_3__*) ; 

__attribute__((used)) static int check_loop(struct Qdisc *q, struct Qdisc *p, int depth)
{
	struct check_loop_arg	arg;

	if (q->ops->cl_ops == NULL)
		return 0;

	arg.w.stop = arg.w.skip = arg.w.count = 0;
	arg.w.fn = check_loop_fn;
	arg.depth = depth;
	arg.p = p;
	q->ops->cl_ops->walk(q, &arg.w);
	return arg.w.stop ? -ELOOP : 0;
}