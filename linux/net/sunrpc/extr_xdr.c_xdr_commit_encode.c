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
struct TYPE_2__ {int iov_len; int /*<<< orphan*/  iov_base; } ;
struct xdr_stream {TYPE_1__ scratch; scalar_t__ p; int /*<<< orphan*/ * page_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memmove (void*,void*,int) ; 
 void* page_address (int /*<<< orphan*/ ) ; 

inline void xdr_commit_encode(struct xdr_stream *xdr)
{
	int shift = xdr->scratch.iov_len;
	void *page;

	if (shift == 0)
		return;
	page = page_address(*xdr->page_ptr);
	memcpy(xdr->scratch.iov_base, page, shift);
	memmove(page, page + shift, (void *)xdr->p - page);
	xdr->scratch.iov_len = 0;
}