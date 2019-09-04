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
struct xdr_buf {unsigned long page_base; unsigned int page_len; TYPE_1__* tail; } ;
struct svcxprt_rdma {int sc_max_send_sges; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ iov_len; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ min_t (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static bool svc_rdma_pull_up_needed(struct svcxprt_rdma *rdma,
				    struct xdr_buf *xdr,
				    __be32 *wr_lst)
{
	int elements;

	/* xdr->head */
	elements = 1;

	/* xdr->pages */
	if (!wr_lst) {
		unsigned int remaining;
		unsigned long pageoff;

		pageoff = xdr->page_base & ~PAGE_MASK;
		remaining = xdr->page_len;
		while (remaining) {
			++elements;
			remaining -= min_t(u32, PAGE_SIZE - pageoff,
					   remaining);
			pageoff = 0;
		}
	}

	/* xdr->tail */
	if (xdr->tail[0].iov_len)
		++elements;

	/* assume 1 SGE is needed for the transport header */
	return elements >= rdma->sc_max_send_sges;
}