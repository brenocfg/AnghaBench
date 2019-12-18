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
typedef  int uint32_t ;
struct xdr_stream {int dummy; } ;
struct nfs_fh {int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int NFS4_FHSIZE ; 
 int /*<<< orphan*/  OP_GETFH ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int decode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct nfs_fh*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_getfh(struct xdr_stream *xdr, struct nfs_fh *fh)
{
	__be32 *p;
	uint32_t len;
	int status;

	/* Zero handle first to allow comparisons */
	memset(fh, 0, sizeof(*fh));

	status = decode_op_hdr(xdr, OP_GETFH);
	if (status)
		return status;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EIO;
	len = be32_to_cpup(p);
	if (len > NFS4_FHSIZE)
		return -EIO;
	fh->size = len;
	p = xdr_inline_decode(xdr, len);
	if (unlikely(!p))
		return -EIO;
	memcpy(fh->data, p, len);
	return 0;
}