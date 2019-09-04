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
struct gssp_in_token {int /*<<< orphan*/  page_len; int /*<<< orphan*/  page_base; int /*<<< orphan*/  pages; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  xdr_write_pages (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gssx_enc_in_token(struct xdr_stream *xdr,
			     const struct gssp_in_token *in)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	if (!p)
		return -ENOSPC;
	*p = cpu_to_be32(in->page_len);

	/* all we need to do is to write pages */
	xdr_write_pages(xdr, in->pages, in->page_base, in->page_len);

	return 0;
}