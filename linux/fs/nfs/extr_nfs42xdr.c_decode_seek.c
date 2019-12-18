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
struct nfs42_seek_res {int /*<<< orphan*/  sr_offset; int /*<<< orphan*/  sr_eof; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OP_SEEK ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 int decode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_seek(struct xdr_stream *xdr, struct nfs42_seek_res *res)
{
	int status;
	__be32 *p;

	status = decode_op_hdr(xdr, OP_SEEK);
	if (status)
		return status;

	p = xdr_inline_decode(xdr, 4 + 8);
	if (unlikely(!p))
		return -EIO;

	res->sr_eof = be32_to_cpup(p++);
	p = xdr_decode_hyper(p, &res->sr_offset);
	return 0;
}