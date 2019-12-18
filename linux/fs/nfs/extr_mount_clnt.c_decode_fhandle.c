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
struct nfs_fh {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
struct mountres {struct nfs_fh* fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NFS2_FHSIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_fhandle(struct xdr_stream *xdr, struct mountres *res)
{
	struct nfs_fh *fh = res->fh;
	__be32 *p;

	p = xdr_inline_decode(xdr, NFS2_FHSIZE);
	if (unlikely(p == NULL))
		return -EIO;

	fh->size = NFS2_FHSIZE;
	memcpy(fh->data, p, NFS2_FHSIZE);
	return 0;
}