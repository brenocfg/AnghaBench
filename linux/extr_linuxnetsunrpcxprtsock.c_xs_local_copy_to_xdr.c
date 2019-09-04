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
struct xdr_skb_reader {int offset; scalar_t__ count; struct sk_buff* skb; } ;
struct xdr_buf {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  rpc_fraghdr ;

/* Variables and functions */
 scalar_t__ xdr_partial_copy_from_skb (struct xdr_buf*,int /*<<< orphan*/ ,struct xdr_skb_reader*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_skb_read_bits ; 

__attribute__((used)) static int xs_local_copy_to_xdr(struct xdr_buf *xdr, struct sk_buff *skb)
{
	struct xdr_skb_reader desc = {
		.skb		= skb,
		.offset		= sizeof(rpc_fraghdr),
		.count		= skb->len - sizeof(rpc_fraghdr),
	};

	if (xdr_partial_copy_from_skb(xdr, 0, &desc, xdr_skb_read_bits) < 0)
		return -1;
	if (desc.count)
		return -1;
	return 0;
}