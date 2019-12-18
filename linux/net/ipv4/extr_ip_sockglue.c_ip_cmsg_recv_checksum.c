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
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  csum; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  IP_CHECKSUM ; 
 int /*<<< orphan*/  SOL_IP ; 
 int /*<<< orphan*/  csum_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static void ip_cmsg_recv_checksum(struct msghdr *msg, struct sk_buff *skb,
				  int tlen, int offset)
{
	__wsum csum = skb->csum;

	if (skb->ip_summed != CHECKSUM_COMPLETE)
		return;

	if (offset != 0) {
		int tend_off = skb_transport_offset(skb) + tlen;
		csum = csum_sub(csum, skb_checksum(skb, tend_off, offset, 0));
	}

	put_cmsg(msg, SOL_IP, IP_CHECKSUM, sizeof(__wsum), &csum);
}