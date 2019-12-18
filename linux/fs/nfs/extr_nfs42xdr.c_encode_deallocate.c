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
struct nfs42_falloc_args {int dummy; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_DEALLOCATE ; 
 int /*<<< orphan*/  decode_deallocate_maxsz ; 
 int /*<<< orphan*/  encode_fallocate (struct xdr_stream*,struct nfs42_falloc_args const*) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 

__attribute__((used)) static void encode_deallocate(struct xdr_stream *xdr,
			      const struct nfs42_falloc_args *args,
			      struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_DEALLOCATE, decode_deallocate_maxsz, hdr);
	encode_fallocate(xdr, args);
}