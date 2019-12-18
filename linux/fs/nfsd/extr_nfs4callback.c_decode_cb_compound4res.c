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
typedef  int u32 ;
struct xdr_stream {int dummy; } ;
struct nfs4_cb_compound_hdr {void* nops; void* status; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  XDR_QUADLEN (int) ; 
 void* be32_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_cb_compound4res(struct xdr_stream *xdr,
				  struct nfs4_cb_compound_hdr *hdr)
{
	u32 length;
	__be32 *p;

	p = xdr_inline_decode(xdr, 4 + 4);
	if (unlikely(p == NULL))
		goto out_overflow;
	hdr->status = be32_to_cpup(p++);
	/* Ignore the tag */
	length = be32_to_cpup(p++);
	p = xdr_inline_decode(xdr, length + 4);
	if (unlikely(p == NULL))
		goto out_overflow;
	p += XDR_QUADLEN(length);
	hdr->nops = be32_to_cpup(p);
	return 0;
out_overflow:
	return -EIO;
}