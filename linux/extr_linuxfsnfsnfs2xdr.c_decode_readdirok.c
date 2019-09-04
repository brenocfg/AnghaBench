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
struct xdr_stream {TYPE_1__* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_len; } ;

/* Variables and functions */
 int xdr_read_pages (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_readdirok(struct xdr_stream *xdr)
{
	return xdr_read_pages(xdr, xdr->buf->page_len);
}