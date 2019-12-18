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

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OP_SETATTR ; 
 scalar_t__ decode_bitmap4 (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int decode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_setattr(struct xdr_stream *xdr)
{
	int status;

	status = decode_op_hdr(xdr, OP_SETATTR);
	if (status)
		return status;
	if (decode_bitmap4(xdr, NULL, 0) >= 0)
		return 0;
	return -EIO;
}