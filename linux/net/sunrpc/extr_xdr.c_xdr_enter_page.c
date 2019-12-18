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

/* Variables and functions */
 unsigned int xdr_align_pages (struct xdr_stream*,unsigned int) ; 
 int /*<<< orphan*/  xdr_set_page_base (struct xdr_stream*,int /*<<< orphan*/ ,unsigned int) ; 

void xdr_enter_page(struct xdr_stream *xdr, unsigned int len)
{
	len = xdr_align_pages(xdr, len);
	/*
	 * Position current pointer at beginning of tail, and
	 * set remaining message length.
	 */
	if (len != 0)
		xdr_set_page_base(xdr, 0, len);
}