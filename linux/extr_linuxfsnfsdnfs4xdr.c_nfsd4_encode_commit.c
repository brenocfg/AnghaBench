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
struct nfsd4_compoundres {struct xdr_stream xdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct nfsd4_commit {TYPE_1__ co_verf; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_VERIFIER_SIZE ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd4_encode_commit(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_commit *commit)
{
	struct xdr_stream *xdr = &resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_VERIFIER_SIZE);
	if (!p)
		return nfserr_resource;
	p = xdr_encode_opaque_fixed(p, commit->co_verf.data,
						NFS4_VERIFIER_SIZE);
	return 0;
}