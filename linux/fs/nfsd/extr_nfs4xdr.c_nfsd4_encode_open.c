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
struct nfsd4_open {int op_rflags; int op_delegate_type; int op_recall; int op_why_no_deleg; int /*<<< orphan*/  op_delegate_stateid; int /*<<< orphan*/ * op_bmval; int /*<<< orphan*/  op_cinfo; int /*<<< orphan*/  op_stateid; } ;
struct nfsd4_compoundres {struct xdr_stream xdr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE ; 
 int NFS4_LIMIT_SIZE ; 
#define  NFS4_OPEN_DELEGATE_NONE 133 
#define  NFS4_OPEN_DELEGATE_NONE_EXT 132 
#define  NFS4_OPEN_DELEGATE_READ 131 
#define  NFS4_OPEN_DELEGATE_WRITE 130 
#define  WND4_CONTENTION 129 
#define  WND4_RESOURCE 128 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/ * encode_cinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_encode_bitmap (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_encode_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32
nfsd4_encode_open(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_open *open)
{
	struct xdr_stream *xdr = &resp->xdr;
	__be32 *p;

	nfserr = nfsd4_encode_stateid(xdr, &open->op_stateid);
	if (nfserr)
		return nfserr;
	p = xdr_reserve_space(xdr, 24);
	if (!p)
		return nfserr_resource;
	p = encode_cinfo(p, &open->op_cinfo);
	*p++ = cpu_to_be32(open->op_rflags);

	nfserr = nfsd4_encode_bitmap(xdr, open->op_bmval[0], open->op_bmval[1],
					open->op_bmval[2]);
	if (nfserr)
		return nfserr;

	p = xdr_reserve_space(xdr, 4);
	if (!p)
		return nfserr_resource;

	*p++ = cpu_to_be32(open->op_delegate_type);
	switch (open->op_delegate_type) {
	case NFS4_OPEN_DELEGATE_NONE:
		break;
	case NFS4_OPEN_DELEGATE_READ:
		nfserr = nfsd4_encode_stateid(xdr, &open->op_delegate_stateid);
		if (nfserr)
			return nfserr;
		p = xdr_reserve_space(xdr, 20);
		if (!p)
			return nfserr_resource;
		*p++ = cpu_to_be32(open->op_recall);

		/*
		 * TODO: ACE's in delegations
		 */
		*p++ = cpu_to_be32(NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);   /* XXX: is NULL principal ok? */
		break;
	case NFS4_OPEN_DELEGATE_WRITE:
		nfserr = nfsd4_encode_stateid(xdr, &open->op_delegate_stateid);
		if (nfserr)
			return nfserr;
		p = xdr_reserve_space(xdr, 32);
		if (!p)
			return nfserr_resource;
		*p++ = cpu_to_be32(0);

		/*
		 * TODO: space_limit's in delegations
		 */
		*p++ = cpu_to_be32(NFS4_LIMIT_SIZE);
		*p++ = cpu_to_be32(~(u32)0);
		*p++ = cpu_to_be32(~(u32)0);

		/*
		 * TODO: ACE's in delegations
		 */
		*p++ = cpu_to_be32(NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);   /* XXX: is NULL principal ok? */
		break;
	case NFS4_OPEN_DELEGATE_NONE_EXT: /* 4.1 */
		switch (open->op_why_no_deleg) {
		case WND4_CONTENTION:
		case WND4_RESOURCE:
			p = xdr_reserve_space(xdr, 8);
			if (!p)
				return nfserr_resource;
			*p++ = cpu_to_be32(open->op_why_no_deleg);
			/* deleg signaling not supported yet: */
			*p++ = cpu_to_be32(0);
			break;
		default:
			p = xdr_reserve_space(xdr, 4);
			if (!p)
				return nfserr_resource;
			*p++ = cpu_to_be32(open->op_why_no_deleg);
		}
		break;
	default:
		BUG();
	}
	/* XXX save filehandle here */
	return 0;
}