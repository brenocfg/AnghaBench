#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; scalar_t__ sin6_flowinfo; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
union sctp_addr {TYPE_3__ v6; TYPE_2__ v4; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct sctphdr {int /*<<< orphan*/  source; } ;
struct TYPE_10__ {int version; int /*<<< orphan*/  saddr; } ;
struct TYPE_9__ {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int IPV6_ADDR_LINKLOCAL ; 
 TYPE_5__* ip_hdr (struct sk_buff*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 TYPE_4__* ipv6_hdr (struct sk_buff*) ; 
 struct sctphdr* sctp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_sk (int /*<<< orphan*/ ) ; 
 int sctp_v6_addr_to_user (int /*<<< orphan*/ ,union sctp_addr*) ; 
 scalar_t__ sctp_v6_skb_iif (struct sk_buff*) ; 

__attribute__((used)) static void sctp_inet6_skb_msgname(struct sk_buff *skb, char *msgname,
				   int *addr_len)
{
	union sctp_addr *addr;
	struct sctphdr *sh;

	if (!msgname)
		return;

	addr = (union sctp_addr *)msgname;
	sh = sctp_hdr(skb);

	if (ip_hdr(skb)->version == 4) {
		addr->v4.sin_family = AF_INET;
		addr->v4.sin_port = sh->source;
		addr->v4.sin_addr.s_addr = ip_hdr(skb)->saddr;
	} else {
		addr->v6.sin6_family = AF_INET6;
		addr->v6.sin6_flowinfo = 0;
		addr->v6.sin6_port = sh->source;
		addr->v6.sin6_addr = ipv6_hdr(skb)->saddr;
		if (ipv6_addr_type(&addr->v6.sin6_addr) & IPV6_ADDR_LINKLOCAL)
			addr->v6.sin6_scope_id = sctp_v6_skb_iif(skb);
		else
			addr->v6.sin6_scope_id = 0;
	}

	*addr_len = sctp_v6_addr_to_user(sctp_sk(skb->sk), addr);
}