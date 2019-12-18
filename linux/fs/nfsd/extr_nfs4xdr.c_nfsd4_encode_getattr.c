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
struct svc_fh {int /*<<< orphan*/  fh_dentry; int /*<<< orphan*/  fh_export; } ;
struct nfsd4_getattr {int /*<<< orphan*/  ga_bmval; struct svc_fh* ga_fhp; } ;
struct nfsd4_compoundres {int /*<<< orphan*/  rqstp; struct xdr_stream xdr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd4_encode_fattr (struct xdr_stream*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd4_encode_getattr(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_getattr *getattr)
{
	struct svc_fh *fhp = getattr->ga_fhp;
	struct xdr_stream *xdr = &resp->xdr;

	return nfsd4_encode_fattr(xdr, fhp, fhp->fh_export, fhp->fh_dentry,
				    getattr->ga_bmval, resp->rqstp, 0);
}