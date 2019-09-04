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
struct rpc_rqst {size_t rq_callsize; char* rq_rbuffer; scalar_t__ rq_buffer; } ;
struct rpc_buffer {int len; scalar_t__ data; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,size_t) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 struct rpc_buffer* page_address (struct page*) ; 

__attribute__((used)) static int bc_malloc(struct rpc_task *task)
{
	struct rpc_rqst *rqst = task->tk_rqstp;
	size_t size = rqst->rq_callsize;
	struct page *page;
	struct rpc_buffer *buf;

	if (size > PAGE_SIZE - sizeof(struct rpc_buffer)) {
		WARN_ONCE(1, "xprtsock: large bc buffer request (size %zu)\n",
			  size);
		return -EINVAL;
	}

	page = alloc_page(GFP_KERNEL);
	if (!page)
		return -ENOMEM;

	buf = page_address(page);
	buf->len = PAGE_SIZE;

	rqst->rq_buffer = buf->data;
	rqst->rq_rbuffer = (char *)rqst->rq_buffer + rqst->rq_callsize;
	return 0;
}