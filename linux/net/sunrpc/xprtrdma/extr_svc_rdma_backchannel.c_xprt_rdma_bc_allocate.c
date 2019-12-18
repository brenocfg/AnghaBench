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
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {size_t rq_callsize; int /*<<< orphan*/  rq_rbuffer; int /*<<< orphan*/  rq_rcvsize; int /*<<< orphan*/  rq_buffer; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  RPCRDMA_DEF_GFP ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,size_t) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int
xprt_rdma_bc_allocate(struct rpc_task *task)
{
	struct rpc_rqst *rqst = task->tk_rqstp;
	size_t size = rqst->rq_callsize;
	struct page *page;

	if (size > PAGE_SIZE) {
		WARN_ONCE(1, "svcrdma: large bc buffer request (size %zu)\n",
			  size);
		return -EINVAL;
	}

	page = alloc_page(RPCRDMA_DEF_GFP);
	if (!page)
		return -ENOMEM;
	rqst->rq_buffer = page_address(page);

	rqst->rq_rbuffer = kmalloc(rqst->rq_rcvsize, RPCRDMA_DEF_GFP);
	if (!rqst->rq_rbuffer) {
		put_page(page);
		return -ENOMEM;
	}
	return 0;
}