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
struct udphdr {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct pdp_ctx {int dummy; } ;
struct gtp_dev {int /*<<< orphan*/  role; int /*<<< orphan*/  dev; } ;
struct gtp0_header {int flags; scalar_t__ type; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 scalar_t__ GTP_TPDU ; 
 int GTP_V0 ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct pdp_ctx* gtp0_pdp_find (struct gtp_dev*,int /*<<< orphan*/ ) ; 
 int gtp_rx (struct pdp_ctx*,struct sk_buff*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int gtp0_udp_encap_recv(struct gtp_dev *gtp, struct sk_buff *skb)
{
	unsigned int hdrlen = sizeof(struct udphdr) +
			      sizeof(struct gtp0_header);
	struct gtp0_header *gtp0;
	struct pdp_ctx *pctx;

	if (!pskb_may_pull(skb, hdrlen))
		return -1;

	gtp0 = (struct gtp0_header *)(skb->data + sizeof(struct udphdr));

	if ((gtp0->flags >> 5) != GTP_V0)
		return 1;

	if (gtp0->type != GTP_TPDU)
		return 1;

	pctx = gtp0_pdp_find(gtp, be64_to_cpu(gtp0->tid));
	if (!pctx) {
		netdev_dbg(gtp->dev, "No PDP ctx to decap skb=%p\n", skb);
		return 1;
	}

	return gtp_rx(pctx, skb, hdrlen, gtp->role);
}