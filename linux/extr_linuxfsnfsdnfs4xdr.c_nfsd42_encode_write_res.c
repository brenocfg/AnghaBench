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
struct nfsd4_compoundres {int /*<<< orphan*/  xdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct nfsd42_write_res {TYPE_1__ wr_verifier; int /*<<< orphan*/  wr_stable_how; int /*<<< orphan*/  wr_bytes_written; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ NFS4_VERIFIER_SIZE ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * xdr_reserve_space (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static __be32
nfsd42_encode_write_res(struct nfsd4_compoundres *resp, struct nfsd42_write_res *write)
{
	__be32 *p;

	p = xdr_reserve_space(&resp->xdr, 4 + 8 + 4 + NFS4_VERIFIER_SIZE);
	if (!p)
		return nfserr_resource;

	*p++ = cpu_to_be32(0);
	p = xdr_encode_hyper(p, write->wr_bytes_written);
	*p++ = cpu_to_be32(write->wr_stable_how);
	p = xdr_encode_opaque_fixed(p, write->wr_verifier.data,
				    NFS4_VERIFIER_SIZE);
	return nfs_ok;
}