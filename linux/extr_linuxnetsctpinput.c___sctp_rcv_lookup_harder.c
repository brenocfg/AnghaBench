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
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct sctp_transport {int dummy; } ;
struct sctp_chunkhdr {scalar_t__ type; int /*<<< orphan*/  length; } ;
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCTP_CID_INIT ; 
 scalar_t__ SCTP_CID_INIT_ACK ; 
 scalar_t__ SCTP_PAD4 (int /*<<< orphan*/ ) ; 
 struct sctp_association* __sctp_rcv_init_lookup (struct net*,struct sk_buff*,union sctp_addr const*,struct sctp_transport**) ; 
 struct sctp_association* __sctp_rcv_walk_lookup (struct net*,struct sk_buff*,union sctp_addr const*,struct sctp_transport**) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ skb_is_gso_sctp (struct sk_buff*) ; 

__attribute__((used)) static struct sctp_association *__sctp_rcv_lookup_harder(struct net *net,
				      struct sk_buff *skb,
				      const union sctp_addr *laddr,
				      struct sctp_transport **transportp)
{
	struct sctp_chunkhdr *ch;

	/* We do not allow GSO frames here as we need to linearize and
	 * then cannot guarantee frame boundaries. This shouldn't be an
	 * issue as packets hitting this are mostly INIT or INIT-ACK and
	 * those cannot be on GSO-style anyway.
	 */
	if (skb_is_gso(skb) && skb_is_gso_sctp(skb))
		return NULL;

	ch = (struct sctp_chunkhdr *)skb->data;

	/* The code below will attempt to walk the chunk and extract
	 * parameter information.  Before we do that, we need to verify
	 * that the chunk length doesn't cause overflow.  Otherwise, we'll
	 * walk off the end.
	 */
	if (SCTP_PAD4(ntohs(ch->length)) > skb->len)
		return NULL;

	/* If this is INIT/INIT-ACK look inside the chunk too. */
	if (ch->type == SCTP_CID_INIT || ch->type == SCTP_CID_INIT_ACK)
		return __sctp_rcv_init_lookup(net, skb, laddr, transportp);

	return __sctp_rcv_walk_lookup(net, skb, laddr, transportp);
}