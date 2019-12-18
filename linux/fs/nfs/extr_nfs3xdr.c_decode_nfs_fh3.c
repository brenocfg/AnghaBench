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
struct nfs_fh {int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int E2BIG ; 
 int EIO ; 
 int NFS3_FHSIZE ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_nfs_fh3(struct xdr_stream *xdr, struct nfs_fh *fh)
{
	u32 length;
	__be32 *p;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EIO;
	length = be32_to_cpup(p++);
	if (unlikely(length > NFS3_FHSIZE))
		goto out_toobig;
	p = xdr_inline_decode(xdr, length);
	if (unlikely(!p))
		return -EIO;
	fh->size = length;
	memcpy(fh->data, p, length);
	return 0;
out_toobig:
	dprintk("NFS: file handle size (%u) too big\n", length);
	return -E2BIG;
}