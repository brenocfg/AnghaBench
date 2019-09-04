#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct icmphdr {int type; } ;
typedef  int /*<<< orphan*/  _hdr ;
typedef  unsigned int __u32 ;
struct TYPE_3__ {unsigned int data; } ;
struct TYPE_4__ {TYPE_1__ filter; } ;

/* Variables and functions */
 TYPE_2__* raw_sk (struct sock const*) ; 
 struct icmphdr* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct icmphdr*) ; 
 int /*<<< orphan*/  skb_transport_offset (struct sk_buff const*) ; 

__attribute__((used)) static int icmp_filter(const struct sock *sk, const struct sk_buff *skb)
{
	struct icmphdr _hdr;
	const struct icmphdr *hdr;

	hdr = skb_header_pointer(skb, skb_transport_offset(skb),
				 sizeof(_hdr), &_hdr);
	if (!hdr)
		return 1;

	if (hdr->type < 32) {
		__u32 data = raw_sk(sk)->filter.data;

		return ((1U << hdr->type) & data) != 0;
	}

	/* Do not block unknown ICMP types */
	return 0;
}