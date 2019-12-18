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
struct svc_rqst {struct page** rq_pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 unsigned int RPCSVC_MAXPAGES ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct page* alloc_pages_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svc_is_backchannel (struct svc_rqst*) ; 

__attribute__((used)) static int
svc_init_buffer(struct svc_rqst *rqstp, unsigned int size, int node)
{
	unsigned int pages, arghi;

	/* bc_xprt uses fore channel allocated buffers */
	if (svc_is_backchannel(rqstp))
		return 1;

	pages = size / PAGE_SIZE + 1; /* extra page as we hold both request and reply.
				       * We assume one is at most one page
				       */
	arghi = 0;
	WARN_ON_ONCE(pages > RPCSVC_MAXPAGES);
	if (pages > RPCSVC_MAXPAGES)
		pages = RPCSVC_MAXPAGES;
	while (pages) {
		struct page *p = alloc_pages_node(node, GFP_KERNEL, 0);
		if (!p)
			break;
		rqstp->rq_pages[arghi++] = p;
		pages--;
	}
	return pages == 0;
}