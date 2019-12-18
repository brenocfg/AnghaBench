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
struct nfsd4_readlink {int /*<<< orphan*/  rl_fhp; int /*<<< orphan*/  rl_rqstp; } ;
struct nfsd4_compoundres {struct xdr_stream xdr; } ;
typedef  int __be32 ;
struct TYPE_2__ {int len; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int PAGE_SIZE ; 
 int htonl (int) ; 
 int nfsd_readlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int nfserr_inval ; 
 int nfserr_isdir ; 
 int nfserr_resource ; 
 int /*<<< orphan*/  write_bytes_to_xdr_buf (TYPE_1__*,int,int*,int) ; 
 int* xdr_reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  xdr_truncate_encode (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32
nfsd4_encode_readlink(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_readlink *readlink)
{
	int maxcount;
	__be32 wire_count;
	int zero = 0;
	struct xdr_stream *xdr = &resp->xdr;
	int length_offset = xdr->buf->len;
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	if (!p)
		return nfserr_resource;
	maxcount = PAGE_SIZE;

	p = xdr_reserve_space(xdr, maxcount);
	if (!p)
		return nfserr_resource;
	/*
	 * XXX: By default, vfs_readlink() will truncate symlinks if they
	 * would overflow the buffer.  Is this kosher in NFSv4?  If not, one
	 * easy fix is: if vfs_readlink() precisely fills the buffer, assume
	 * that truncation occurred, and return NFS4ERR_RESOURCE.
	 */
	nfserr = nfsd_readlink(readlink->rl_rqstp, readlink->rl_fhp,
						(char *)p, &maxcount);
	if (nfserr == nfserr_isdir)
		nfserr = nfserr_inval;
	if (nfserr) {
		xdr_truncate_encode(xdr, length_offset);
		return nfserr;
	}

	wire_count = htonl(maxcount);
	write_bytes_to_xdr_buf(xdr->buf, length_offset, &wire_count, 4);
	xdr_truncate_encode(xdr, length_offset + 4 + ALIGN(maxcount, 4));
	if (maxcount & 3)
		write_bytes_to_xdr_buf(xdr->buf, length_offset + 4 + maxcount,
						&zero, 4 - (maxcount&3));
	return 0;
}