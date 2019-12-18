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
struct xdr_buf {TYPE_1__* bvec; int /*<<< orphan*/ * pages; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {scalar_t__ bv_offset; int /*<<< orphan*/  bv_len; int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__* kmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 
 size_t xdr_buf_pagecount (struct xdr_buf*) ; 

int
xdr_alloc_bvec(struct xdr_buf *buf, gfp_t gfp)
{
	size_t i, n = xdr_buf_pagecount(buf);

	if (n != 0 && buf->bvec == NULL) {
		buf->bvec = kmalloc_array(n, sizeof(buf->bvec[0]), gfp);
		if (!buf->bvec)
			return -ENOMEM;
		for (i = 0; i < n; i++) {
			buf->bvec[i].bv_page = buf->pages[i];
			buf->bvec[i].bv_len = PAGE_SIZE;
			buf->bvec[i].bv_offset = 0;
		}
	}
	return 0;
}