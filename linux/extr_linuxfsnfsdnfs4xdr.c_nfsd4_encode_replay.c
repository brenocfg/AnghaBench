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
struct nfsd4_op {int /*<<< orphan*/  opnum; struct nfs4_replay* replay; } ;
struct nfs4_replay {scalar_t__ rp_buflen; int /*<<< orphan*/  rp_buf; int /*<<< orphan*/  rp_status; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,scalar_t__) ; 

void
nfsd4_encode_replay(struct xdr_stream *xdr, struct nfsd4_op *op)
{
	__be32 *p;
	struct nfs4_replay *rp = op->replay;

	BUG_ON(!rp);

	p = xdr_reserve_space(xdr, 8 + rp->rp_buflen);
	if (!p) {
		WARN_ON_ONCE(1);
		return;
	}
	*p++ = cpu_to_be32(op->opnum);
	*p++ = rp->rp_status;  /* already xdr'ed */

	p = xdr_encode_opaque_fixed(p, rp->rp_buf, rp->rp_buflen);
}