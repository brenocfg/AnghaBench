#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct seq_file {int dummy; } ;
struct p9_trans_rdma {scalar_t__ port; scalar_t__ sq_depth; scalar_t__ rq_depth; scalar_t__ timeout; scalar_t__ privport; } ;
struct p9_client {struct p9_trans_rdma* trans; } ;

/* Variables and functions */
 scalar_t__ P9_PORT ; 
 scalar_t__ P9_RDMA_RQ_DEPTH ; 
 scalar_t__ P9_RDMA_SQ_DEPTH ; 
 scalar_t__ P9_RDMA_TIMEOUT ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int p9_rdma_show_options(struct seq_file *m, struct p9_client *clnt)
{
	struct p9_trans_rdma *rdma = clnt->trans;

	if (rdma->port != P9_PORT)
		seq_printf(m, ",port=%u", rdma->port);
	if (rdma->sq_depth != P9_RDMA_SQ_DEPTH)
		seq_printf(m, ",sq=%u", rdma->sq_depth);
	if (rdma->rq_depth != P9_RDMA_RQ_DEPTH)
		seq_printf(m, ",rq=%u", rdma->rq_depth);
	if (rdma->timeout != P9_RDMA_TIMEOUT)
		seq_printf(m, ",timeout=%lu", rdma->timeout);
	if (rdma->privport)
		seq_puts(m, ",privport");
	return 0;
}