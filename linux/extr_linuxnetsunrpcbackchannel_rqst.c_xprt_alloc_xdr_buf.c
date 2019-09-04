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
struct xdr_buf {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  xdr_buf_init (struct xdr_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xprt_alloc_xdr_buf(struct xdr_buf *buf, gfp_t gfp_flags)
{
	struct page *page;
	/* Preallocate one XDR receive buffer */
	page = alloc_page(gfp_flags);
	if (page == NULL)
		return -ENOMEM;
	xdr_buf_init(buf, page_address(page), PAGE_SIZE);
	return 0;
}