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
struct nfs_pgio_args {int /*<<< orphan*/  count; int /*<<< orphan*/  offset; int /*<<< orphan*/  stateid; } ;
struct compound_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  OP_READ ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_read_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_read(struct xdr_stream *xdr, const struct nfs_pgio_args *args,
			struct compound_hdr *hdr)
{
	__be32 *p;

	encode_op_hdr(xdr, OP_READ, decode_read_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->stateid);

	p = reserve_space(xdr, 12);
	p = xdr_encode_hyper(p, args->offset);
	*p = cpu_to_be32(args->count);
}