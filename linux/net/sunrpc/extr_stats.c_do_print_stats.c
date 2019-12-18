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
struct seq_file {int dummy; } ;
struct rpc_xprt {TYPE_1__* ops; } ;
struct rpc_clnt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* print_stats ) (struct rpc_xprt*,struct seq_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rpc_xprt*,struct seq_file*) ; 

__attribute__((used)) static int do_print_stats(struct rpc_clnt *clnt, struct rpc_xprt *xprt, void *seqv)
{
	struct seq_file *seq = seqv;

	xprt->ops->print_stats(xprt, seq);
	return 0;
}