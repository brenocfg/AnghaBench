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
struct sk_buff {int dummy; } ;
struct dn_skb_cb {int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dn_nsp_do_disc (int /*<<< orphan*/ *,unsigned char,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 

void dn_nsp_return_disc(struct sk_buff *skb, unsigned char msgflg,
			unsigned short reason)
{
	struct dn_skb_cb *cb = DN_SKB_CB(skb);
	int ddl = 0;
	gfp_t gfp = GFP_ATOMIC;

	dn_nsp_do_disc(NULL, msgflg, reason, gfp, skb_dst(skb), ddl,
			NULL, cb->src_port, cb->dst_port);
}