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
struct nfs42_seek_args {int /*<<< orphan*/  sa_what; int /*<<< orphan*/  sa_offset; int /*<<< orphan*/  sa_stateid; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_SEEK ; 
 int /*<<< orphan*/  decode_seek_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_uint32 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_uint64 (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_seek(struct xdr_stream *xdr,
			const struct nfs42_seek_args *args,
			struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_SEEK, decode_seek_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->sa_stateid);
	encode_uint64(xdr, args->sa_offset);
	encode_uint32(xdr, args->sa_what);
}