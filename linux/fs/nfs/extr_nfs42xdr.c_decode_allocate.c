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
struct nfs42_falloc_res {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ALLOCATE ; 
 int decode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_allocate(struct xdr_stream *xdr, struct nfs42_falloc_res *res)
{
	return decode_op_hdr(xdr, OP_ALLOCATE);
}