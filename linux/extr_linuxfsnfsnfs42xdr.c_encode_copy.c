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
struct nfs42_copy_args {int sync; int /*<<< orphan*/  count; int /*<<< orphan*/  dst_pos; int /*<<< orphan*/  src_pos; int /*<<< orphan*/  dst_stateid; int /*<<< orphan*/  src_stateid; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_COPY ; 
 int /*<<< orphan*/  decode_copy_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_uint32 (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  encode_uint64 (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_copy(struct xdr_stream *xdr,
			const struct nfs42_copy_args *args,
			struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_COPY, decode_copy_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->src_stateid);
	encode_nfs4_stateid(xdr, &args->dst_stateid);

	encode_uint64(xdr, args->src_pos);
	encode_uint64(xdr, args->dst_pos);
	encode_uint64(xdr, args->count);

	encode_uint32(xdr, 1); /* consecutive = true */
	encode_uint32(xdr, args->sync);
	encode_uint32(xdr, 0); /* src server list */
}