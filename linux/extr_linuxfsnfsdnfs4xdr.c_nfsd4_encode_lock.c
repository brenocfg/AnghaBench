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
struct nfsd4_lock {int /*<<< orphan*/  lk_denied; int /*<<< orphan*/  lk_resp_stateid; } ;
struct nfsd4_compoundres {struct xdr_stream xdr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd4_encode_lock_denied (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_encode_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfserr_denied ; 

__attribute__((used)) static __be32
nfsd4_encode_lock(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_lock *lock)
{
	struct xdr_stream *xdr = &resp->xdr;

	if (!nfserr)
		nfserr = nfsd4_encode_stateid(xdr, &lock->lk_resp_stateid);
	else if (nfserr == nfserr_denied)
		nfserr = nfsd4_encode_lock_denied(xdr, &lock->lk_denied);

	return nfserr;
}