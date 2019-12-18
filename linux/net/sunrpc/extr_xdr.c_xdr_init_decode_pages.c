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
struct xdr_stream {int dummy; } ;
struct xdr_buf {unsigned int page_len; unsigned int buflen; unsigned int len; struct page** pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct xdr_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xdr_init_decode (struct xdr_stream*,struct xdr_buf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void xdr_init_decode_pages(struct xdr_stream *xdr, struct xdr_buf *buf,
			   struct page **pages, unsigned int len)
{
	memset(buf, 0, sizeof(*buf));
	buf->pages =  pages;
	buf->page_len =  len;
	buf->buflen =  len;
	buf->len = len;
	xdr_init_decode(xdr, buf, NULL, NULL);
}