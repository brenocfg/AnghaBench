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
struct TYPE_2__ {int /*<<< orphan*/  cb_stateid; } ;
struct nfsd4_copy {TYPE_1__ cp_res; } ;
struct nfs4_cb_compound_hdr {int /*<<< orphan*/  nops; } ;
struct knfsd_fh {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  OP_CB_OFFLOAD ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nfs_fh4 (struct xdr_stream*,struct knfsd_fh const*) ; 
 int /*<<< orphan*/  encode_offload_info4 (struct xdr_stream*,int /*<<< orphan*/ ,struct nfsd4_copy const*) ; 
 int /*<<< orphan*/  encode_stateid4 (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_cb_offload4args(struct xdr_stream *xdr,
				   __be32 nfserr,
				   const struct knfsd_fh *fh,
				   const struct nfsd4_copy *cp,
				   struct nfs4_cb_compound_hdr *hdr)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	*p++ = cpu_to_be32(OP_CB_OFFLOAD);
	encode_nfs_fh4(xdr, fh);
	encode_stateid4(xdr, &cp->cp_res.cb_stateid);
	encode_offload_info4(xdr, nfserr, cp);

	hdr->nops++;
}