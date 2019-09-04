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
typedef  enum nfs_opnum4 { ____Placeholder_nfs_opnum4 } nfs_opnum4 ;

/* Variables and functions */
 int /*<<< orphan*/  __decode_op_hdr (struct xdr_stream*,int,int*) ; 

__attribute__((used)) static int decode_op_hdr(struct xdr_stream *xdr, enum nfs_opnum4 expected)
{
	int retval;

	__decode_op_hdr(xdr, expected, &retval);
	return retval;
}