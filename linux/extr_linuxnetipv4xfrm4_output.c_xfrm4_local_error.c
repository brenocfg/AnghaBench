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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  sk; scalar_t__ encapsulation; } ;
struct iphdr {int /*<<< orphan*/  daddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  inet_dport; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 TYPE_1__* inet_sk (int /*<<< orphan*/ ) ; 
 struct iphdr* inner_ip_hdr (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_local_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xfrm4_local_error(struct sk_buff *skb, u32 mtu)
{
	struct iphdr *hdr;

	hdr = skb->encapsulation ? inner_ip_hdr(skb) : ip_hdr(skb);
	ip_local_error(skb->sk, EMSGSIZE, hdr->daddr,
		       inet_sk(skb->sk)->inet_dport, mtu);
}