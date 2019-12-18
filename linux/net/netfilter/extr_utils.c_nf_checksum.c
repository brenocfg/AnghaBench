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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  nf_ip6_checksum (struct sk_buff*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ip_checksum (struct sk_buff*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__sum16 nf_checksum(struct sk_buff *skb, unsigned int hook,
		    unsigned int dataoff, u8 protocol,
		    unsigned short family)
{
	__sum16 csum = 0;

	switch (family) {
	case AF_INET:
		csum = nf_ip_checksum(skb, hook, dataoff, protocol);
		break;
	case AF_INET6:
		csum = nf_ip6_checksum(skb, hook, dataoff, protocol);
		break;
	}

	return csum;
}