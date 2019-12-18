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
struct sk_buff {scalar_t__ data; } ;
struct sctphdr {scalar_t__ checksum; } ;
struct ipv6hdr {int dummy; } ;
struct ip_vs_protocol {int dummy; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int AF_INET6 ; 
 int /*<<< orphan*/  IP_VS_DBG_RL_PKT (int /*<<< orphan*/ ,int,struct ip_vs_protocol*,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 unsigned int ip_hdrlen (struct sk_buff*) ; 
 scalar_t__ sctp_compute_cksum (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int
sctp_csum_check(int af, struct sk_buff *skb, struct ip_vs_protocol *pp)
{
	unsigned int sctphoff;
	struct sctphdr *sh;
	__le32 cmp, val;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		sctphoff = sizeof(struct ipv6hdr);
	else
#endif
		sctphoff = ip_hdrlen(skb);

	sh = (struct sctphdr *)(skb->data + sctphoff);
	cmp = sh->checksum;
	val = sctp_compute_cksum(skb, sctphoff);

	if (val != cmp) {
		/* CRC failure, dump it. */
		IP_VS_DBG_RL_PKT(0, af, pp, skb, 0,
				"Failed checksum for");
		return 0;
	}
	return 1;
}