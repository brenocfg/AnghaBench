#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {TYPE_3__* buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct nfsd4_sequence {scalar_t__ status_flags; scalar_t__ maxslots; scalar_t__ slotid; scalar_t__ seqid; TYPE_1__ sessionid; } ;
struct TYPE_5__ {int /*<<< orphan*/  data_offset; } ;
struct nfsd4_compoundres {TYPE_2__ cstate; struct xdr_stream xdr; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 scalar_t__ NFS4_MAX_SESSIONID_LEN ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,scalar_t__) ; 

__attribute__((used)) static __be32
nfsd4_encode_sequence(struct nfsd4_compoundres *resp, __be32 nfserr,
		      struct nfsd4_sequence *seq)
{
	struct xdr_stream *xdr = &resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_MAX_SESSIONID_LEN + 20);
	if (!p)
		return nfserr_resource;
	p = xdr_encode_opaque_fixed(p, seq->sessionid.data,
					NFS4_MAX_SESSIONID_LEN);
	*p++ = cpu_to_be32(seq->seqid);
	*p++ = cpu_to_be32(seq->slotid);
	/* Note slotid's are numbered from zero: */
	*p++ = cpu_to_be32(seq->maxslots - 1); /* sr_highest_slotid */
	*p++ = cpu_to_be32(seq->maxslots - 1); /* sr_target_highest_slotid */
	*p++ = cpu_to_be32(seq->status_flags);

	resp->cstate.data_offset = xdr->buf->len; /* DRC cache data pointer */
	return 0;
}