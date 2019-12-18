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
struct svcxprt_rdma {int /*<<< orphan*/  sc_rw_ctxt_lock; int /*<<< orphan*/  sc_rw_ctxts; } ;
struct TYPE_2__ {int /*<<< orphan*/  sgl; } ;
struct svc_rdma_rw_ctxt {TYPE_1__ rw_sg_table; int /*<<< orphan*/  rw_first_sgl; int /*<<< orphan*/  rw_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SG_CHUNK_SIZE ; 
 int /*<<< orphan*/  kfree (struct svc_rdma_rw_ctxt*) ; 
 struct svc_rdma_rw_ctxt* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_first_sgl ; 
 scalar_t__ sg_alloc_table_chained (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct svc_rdma_rw_ctxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct svc_rdma_rw_ctxt* svc_rdma_next_ctxt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct svc_rdma_rw_ctxt *
svc_rdma_get_rw_ctxt(struct svcxprt_rdma *rdma, unsigned int sges)
{
	struct svc_rdma_rw_ctxt *ctxt;

	spin_lock(&rdma->sc_rw_ctxt_lock);

	ctxt = svc_rdma_next_ctxt(&rdma->sc_rw_ctxts);
	if (ctxt) {
		list_del(&ctxt->rw_list);
		spin_unlock(&rdma->sc_rw_ctxt_lock);
	} else {
		spin_unlock(&rdma->sc_rw_ctxt_lock);
		ctxt = kmalloc(struct_size(ctxt, rw_first_sgl, SG_CHUNK_SIZE),
			       GFP_KERNEL);
		if (!ctxt)
			goto out;
		INIT_LIST_HEAD(&ctxt->rw_list);
	}

	ctxt->rw_sg_table.sgl = ctxt->rw_first_sgl;
	if (sg_alloc_table_chained(&ctxt->rw_sg_table, sges,
				   ctxt->rw_sg_table.sgl,
				   SG_CHUNK_SIZE)) {
		kfree(ctxt);
		ctxt = NULL;
	}
out:
	return ctxt;
}