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
struct TYPE_4__ {unsigned int mrs_allocated; } ;
struct rpcrdma_ia {TYPE_1__* ri_ops; } ;
struct rpcrdma_buffer {int /*<<< orphan*/  rb_mrlock; int /*<<< orphan*/  rb_all; int /*<<< orphan*/  rb_mrs; } ;
struct rpcrdma_xprt {int /*<<< orphan*/  rx_xprt; TYPE_2__ rx_stats; struct rpcrdma_ia rx_ia; struct rpcrdma_buffer rx_buf; } ;
struct rpcrdma_mr {int /*<<< orphan*/  mr_all; int /*<<< orphan*/  mr_list; struct rpcrdma_xprt* mr_xprt; } ;
struct TYPE_3__ {int (* ro_init_mr ) (struct rpcrdma_ia*,struct rpcrdma_mr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  kfree (struct rpcrdma_mr*) ; 
 struct rpcrdma_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct rpcrdma_ia*,struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  trace_xprtrdma_createmrs (struct rpcrdma_xprt*,unsigned int) ; 
 int /*<<< orphan*/  xprt_write_space (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rpcrdma_mrs_create(struct rpcrdma_xprt *r_xprt)
{
	struct rpcrdma_buffer *buf = &r_xprt->rx_buf;
	struct rpcrdma_ia *ia = &r_xprt->rx_ia;
	unsigned int count;
	LIST_HEAD(free);
	LIST_HEAD(all);

	for (count = 0; count < 3; count++) {
		struct rpcrdma_mr *mr;
		int rc;

		mr = kzalloc(sizeof(*mr), GFP_KERNEL);
		if (!mr)
			break;

		rc = ia->ri_ops->ro_init_mr(ia, mr);
		if (rc) {
			kfree(mr);
			break;
		}

		mr->mr_xprt = r_xprt;

		list_add(&mr->mr_list, &free);
		list_add(&mr->mr_all, &all);
	}

	spin_lock(&buf->rb_mrlock);
	list_splice(&free, &buf->rb_mrs);
	list_splice(&all, &buf->rb_all);
	r_xprt->rx_stats.mrs_allocated += count;
	spin_unlock(&buf->rb_mrlock);
	trace_xprtrdma_createmrs(r_xprt, count);

	xprt_write_space(&r_xprt->rx_xprt);
}