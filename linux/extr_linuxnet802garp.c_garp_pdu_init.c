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
struct sk_buff {int /*<<< orphan*/  protocol; TYPE_1__* dev; } ;
struct llc_pdu_un {int dummy; } ;
struct garp_pdu_hdr {int /*<<< orphan*/  protocol; } ;
struct garp_applicant {struct sk_buff* pdu; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  GARP_PROTOCOL_ID ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ LL_RESERVED_SPACE (TYPE_1__*) ; 
 struct garp_pdu_hdr* __skb_put (struct sk_buff*,int) ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int garp_pdu_init(struct garp_applicant *app)
{
	struct sk_buff *skb;
	struct garp_pdu_hdr *gp;

#define LLC_RESERVE	sizeof(struct llc_pdu_un)
	skb = alloc_skb(app->dev->mtu + LL_RESERVED_SPACE(app->dev),
			GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;

	skb->dev = app->dev;
	skb->protocol = htons(ETH_P_802_2);
	skb_reserve(skb, LL_RESERVED_SPACE(app->dev) + LLC_RESERVE);

	gp = __skb_put(skb, sizeof(*gp));
	put_unaligned(htons(GARP_PROTOCOL_ID), &gp->protocol);

	app->pdu = skb;
	return 0;
}