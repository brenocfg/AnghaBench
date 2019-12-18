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
struct svcxprt_rdma {int /*<<< orphan*/  sc_rw_ctxt_lock; int /*<<< orphan*/  sc_rw_ctxts; } ;
struct svc_rdma_rw_ctxt {int /*<<< orphan*/  rw_list; int /*<<< orphan*/  rw_sg_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  SG_CHUNK_SIZE ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_free_table_chained (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void svc_rdma_put_rw_ctxt(struct svcxprt_rdma *rdma,
				 struct svc_rdma_rw_ctxt *ctxt)
{
	sg_free_table_chained(&ctxt->rw_sg_table, SG_CHUNK_SIZE);

	spin_lock(&rdma->sc_rw_ctxt_lock);
	list_add(&ctxt->rw_list, &rdma->sc_rw_ctxts);
	spin_unlock(&rdma->sc_rw_ctxt_lock);
}