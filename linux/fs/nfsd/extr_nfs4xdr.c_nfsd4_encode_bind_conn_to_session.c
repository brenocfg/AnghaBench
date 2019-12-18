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
struct nfsd4_bind_conn_to_session {int /*<<< orphan*/  dir; TYPE_1__ sessionid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ NFS4_MAX_SESSIONID_LEN ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,scalar_t__) ; 

__attribute__((used)) static __be32 nfsd4_encode_bind_conn_to_session(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_bind_conn_to_session *bcts)
{
	struct xdr_stream *xdr = &resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_MAX_SESSIONID_LEN + 8);
	if (!p)
		return nfserr_resource;
	p = xdr_encode_opaque_fixed(p, bcts->sessionid.data,
					NFS4_MAX_SESSIONID_LEN);
	*p++ = cpu_to_be32(bcts->dir);
	/* Upshifting from TCP to RDMA is not supported */
	*p++ = cpu_to_be32(0);
	return 0;
}