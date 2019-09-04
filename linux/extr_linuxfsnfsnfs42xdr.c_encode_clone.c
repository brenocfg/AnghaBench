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
struct nfs42_clone_args {int /*<<< orphan*/  count; int /*<<< orphan*/  dst_offset; int /*<<< orphan*/  src_offset; int /*<<< orphan*/  dst_stateid; int /*<<< orphan*/  src_stateid; } ;
struct compound_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  OP_CLONE ; 
 int /*<<< orphan*/  decode_clone_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_clone(struct xdr_stream *xdr,
			 const struct nfs42_clone_args *args,
			 struct compound_hdr *hdr)
{
	__be32 *p;

	encode_op_hdr(xdr, OP_CLONE, decode_clone_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->src_stateid);
	encode_nfs4_stateid(xdr, &args->dst_stateid);
	p = reserve_space(xdr, 3*8);
	p = xdr_encode_hyper(p, args->src_offset);
	p = xdr_encode_hyper(p, args->dst_offset);
	xdr_encode_hyper(p, args->count);
}