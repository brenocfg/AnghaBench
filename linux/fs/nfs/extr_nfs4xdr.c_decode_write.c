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
struct nfs_pgio_res {TYPE_1__* verf; void* count; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  verifier; void* committed; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OP_WRITE ; 
 void* be32_to_cpup (int /*<<< orphan*/ ) ; 
 int decode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int decode_write_verifier (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_write(struct xdr_stream *xdr, struct nfs_pgio_res *res)
{
	__be32 *p;
	int status;

	status = decode_op_hdr(xdr, OP_WRITE);
	if (status)
		return status;

	p = xdr_inline_decode(xdr, 8);
	if (unlikely(!p))
		return -EIO;
	res->count = be32_to_cpup(p++);
	res->verf->committed = be32_to_cpup(p++);
	return decode_write_verifier(xdr, &res->verf->verifier);
}