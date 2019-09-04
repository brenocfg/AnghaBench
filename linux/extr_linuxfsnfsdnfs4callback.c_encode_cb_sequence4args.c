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
struct nfsd4_session {int /*<<< orphan*/  se_cb_seq_nr; } ;
struct nfsd4_callback {TYPE_1__* cb_clp; } ;
struct nfs4_cb_compound_hdr {scalar_t__ minorversion; int /*<<< orphan*/  nops; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct nfsd4_session* cl_cb_session; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_CB_SEQUENCE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nfs_cb_opnum4 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_sessionid4 (struct xdr_stream*,struct nfsd4_session*) ; 
 int /*<<< orphan*/  xdr_encode_empty_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 
 void* xdr_zero ; 

__attribute__((used)) static void encode_cb_sequence4args(struct xdr_stream *xdr,
				    const struct nfsd4_callback *cb,
				    struct nfs4_cb_compound_hdr *hdr)
{
	struct nfsd4_session *session = cb->cb_clp->cl_cb_session;
	__be32 *p;

	if (hdr->minorversion == 0)
		return;

	encode_nfs_cb_opnum4(xdr, OP_CB_SEQUENCE);
	encode_sessionid4(xdr, session);

	p = xdr_reserve_space(xdr, 4 + 4 + 4 + 4 + 4);
	*p++ = cpu_to_be32(session->se_cb_seq_nr);	/* csa_sequenceid */
	*p++ = xdr_zero;			/* csa_slotid */
	*p++ = xdr_zero;			/* csa_highest_slotid */
	*p++ = xdr_zero;			/* csa_cachethis */
	xdr_encode_empty_array(p);		/* csa_referring_call_lists */

	hdr->nops++;
}