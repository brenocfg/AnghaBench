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
struct TYPE_2__ {long connect_time; int /*<<< orphan*/  pending_u; int /*<<< orphan*/  sending_u; int /*<<< orphan*/  max_slots; int /*<<< orphan*/  bklog_u; int /*<<< orphan*/  req_u; int /*<<< orphan*/  bad_xids; int /*<<< orphan*/  recvs; int /*<<< orphan*/  sends; int /*<<< orphan*/  connect_count; int /*<<< orphan*/  bind_count; } ;
struct rpc_xprt {TYPE_1__ stat; scalar_t__ last_used; } ;

/* Variables and functions */
 long HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xprt_connected (struct rpc_xprt*) ; 

__attribute__((used)) static void xs_local_print_stats(struct rpc_xprt *xprt, struct seq_file *seq)
{
	long idle_time = 0;

	if (xprt_connected(xprt))
		idle_time = (long)(jiffies - xprt->last_used) / HZ;

	seq_printf(seq, "\txprt:\tlocal %lu %lu %lu %ld %lu %lu %lu "
			"%llu %llu %lu %llu %llu\n",
			xprt->stat.bind_count,
			xprt->stat.connect_count,
			xprt->stat.connect_time / HZ,
			idle_time,
			xprt->stat.sends,
			xprt->stat.recvs,
			xprt->stat.bad_xids,
			xprt->stat.req_u,
			xprt->stat.bklog_u,
			xprt->stat.max_slots,
			xprt->stat.sending_u,
			xprt->stat.pending_u);
}