#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_4__ {scalar_t__ sa_family; } ;
union sctp_addr {TYPE_3__ v6; TYPE_2__ v4; TYPE_1__ sa; } ;
struct sk_buff {int dummy; } ;
struct sctp_transport {int dummy; } ;
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 struct sctp_association* __sctp_lookup_association (struct net*,union sctp_addr const*,union sctp_addr const*,struct sctp_transport**) ; 
 struct sctp_association* __sctp_rcv_lookup_harder (struct net*,struct sk_buff*,union sctp_addr const*,struct sctp_transport**) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_association *__sctp_rcv_lookup(struct net *net,
				      struct sk_buff *skb,
				      const union sctp_addr *paddr,
				      const union sctp_addr *laddr,
				      struct sctp_transport **transportp)
{
	struct sctp_association *asoc;

	asoc = __sctp_lookup_association(net, laddr, paddr, transportp);
	if (asoc)
		goto out;

	/* Further lookup for INIT/INIT-ACK packets.
	 * SCTP Implementors Guide, 2.18 Handling of address
	 * parameters within the INIT or INIT-ACK.
	 */
	asoc = __sctp_rcv_lookup_harder(net, skb, laddr, transportp);
	if (asoc)
		goto out;

	if (paddr->sa.sa_family == AF_INET)
		pr_debug("sctp: asoc not found for src:%pI4:%d dst:%pI4:%d\n",
			 &laddr->v4.sin_addr, ntohs(laddr->v4.sin_port),
			 &paddr->v4.sin_addr, ntohs(paddr->v4.sin_port));
	else
		pr_debug("sctp: asoc not found for src:%pI6:%d dst:%pI6:%d\n",
			 &laddr->v6.sin6_addr, ntohs(laddr->v6.sin6_port),
			 &paddr->v6.sin6_addr, ntohs(paddr->v6.sin6_port));

out:
	return asoc;
}