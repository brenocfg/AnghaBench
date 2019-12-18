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
struct nfs42_offload_status_args {int /*<<< orphan*/  osa_stateid; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_OFFLOAD_CANCEL ; 
 int /*<<< orphan*/  decode_offload_cancel_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 

__attribute__((used)) static void encode_offload_cancel(struct xdr_stream *xdr,
				  const struct nfs42_offload_status_args *args,
				  struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_OFFLOAD_CANCEL, decode_offload_cancel_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->osa_stateid);
}