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
struct xdr_stream {int dummy; } ;
struct TYPE_2__ {unsigned int fh_size; int /*<<< orphan*/  fh_base; } ;
struct svc_fh {TYPE_1__ fh_handle; } ;
struct nfsd4_compoundres {struct xdr_stream xdr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/ * xdr_encode_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,unsigned int) ; 

__attribute__((used)) static __be32
nfsd4_encode_getfh(struct nfsd4_compoundres *resp, __be32 nfserr, struct svc_fh **fhpp)
{
	struct xdr_stream *xdr = &resp->xdr;
	struct svc_fh *fhp = *fhpp;
	unsigned int len;
	__be32 *p;

	len = fhp->fh_handle.fh_size;
	p = xdr_reserve_space(xdr, len + 4);
	if (!p)
		return nfserr_resource;
	p = xdr_encode_opaque(p, &fhp->fh_handle.fh_base, len);
	return 0;
}