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
struct compound_hdr {char* tag; int nops; void* status; void* taglen; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  XDR_QUADLEN (void*) ; 
 void* be32_to_cpup (int /*<<< orphan*/ *) ; 
 int nfs4_stat_to_errno (void*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_compound_hdr(struct xdr_stream *xdr, struct compound_hdr *hdr)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, 8);
	if (unlikely(!p))
		return -EIO;
	hdr->status = be32_to_cpup(p++);
	hdr->taglen = be32_to_cpup(p);

	p = xdr_inline_decode(xdr, hdr->taglen + 4);
	if (unlikely(!p))
		return -EIO;
	hdr->tag = (char *)p;
	p += XDR_QUADLEN(hdr->taglen);
	hdr->nops = be32_to_cpup(p);
	if (unlikely(hdr->nops < 1))
		return nfs4_stat_to_errno(hdr->status);
	return 0;
}