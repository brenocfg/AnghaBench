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
typedef  int u32 ;
struct xdr_buf {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  rpc_fraghdr ;

/* Variables and functions */
 int RPC_LAST_STREAM_FRAGMENT ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static rpc_fraghdr
xs_stream_record_marker(struct xdr_buf *xdr)
{
	if (!xdr->len)
		return 0;
	return cpu_to_be32(RPC_LAST_STREAM_FRAGMENT | (u32)xdr->len);
}