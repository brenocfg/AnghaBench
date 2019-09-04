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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_scope_id; scalar_t__ sin6_flowinfo; int /*<<< orphan*/  sin6_family; } ;
union sctp_addr {struct sockaddr_in6 v6; } ;
struct sk_buff {scalar_t__ cb; } ;
struct sctphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct inet6_skb_parm {int /*<<< orphan*/  iif; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 struct sctphdr* sctp_hdr (struct sk_buff*) ; 

__attribute__((used)) static void sctp_v6_from_skb(union sctp_addr *addr, struct sk_buff *skb,
			     int is_saddr)
{
	/* Always called on head skb, so this is safe */
	struct sctphdr *sh = sctp_hdr(skb);
	struct sockaddr_in6 *sa = &addr->v6;

	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_flowinfo = 0; /* FIXME */
	addr->v6.sin6_scope_id = ((struct inet6_skb_parm *)skb->cb)->iif;

	if (is_saddr) {
		sa->sin6_port = sh->source;
		sa->sin6_addr = ipv6_hdr(skb)->saddr;
	} else {
		sa->sin6_port = sh->dest;
		sa->sin6_addr = ipv6_hdr(skb)->daddr;
	}
}