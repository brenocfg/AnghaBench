#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct nfs_locku_args {TYPE_1__* fl; int /*<<< orphan*/  stateid; int /*<<< orphan*/  seqid; } ;
struct compound_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  fl_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_LOCKU ; 
 int /*<<< orphan*/  decode_locku_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_seqid (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_uint32 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_lock_length (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs4_lock_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_locku(struct xdr_stream *xdr, const struct nfs_locku_args *args, struct compound_hdr *hdr)
{
	__be32 *p;

	encode_op_hdr(xdr, OP_LOCKU, decode_locku_maxsz, hdr);
	encode_uint32(xdr, nfs4_lock_type(args->fl, 0));
	encode_nfs4_seqid(xdr, args->seqid);
	encode_nfs4_stateid(xdr, &args->stateid);
	p = reserve_space(xdr, 16);
	p = xdr_encode_hyper(p, args->fl->fl_start);
	xdr_encode_hyper(p, nfs4_lock_length(args->fl));
}