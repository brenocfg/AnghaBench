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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct llc_shdlc {int (* xmit_to_drv ) (int /*<<< orphan*/ ,struct sk_buff*) ;int /*<<< orphan*/  hdev; } ;
typedef  enum sframe_type { ____Placeholder_sframe_type } sframe_type ;

/* Variables and functions */
 int ENOMEM ; 
 int SHDLC_CONTROL_HEAD_S ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* llc_shdlc_alloc_skb (struct llc_shdlc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int llc_shdlc_send_s_frame(struct llc_shdlc *shdlc,
				  enum sframe_type sframe_type, int nr)
{
	int r;
	struct sk_buff *skb;

	pr_debug("sframe_type=%d nr=%d\n", sframe_type, nr);

	skb = llc_shdlc_alloc_skb(shdlc, 0);
	if (skb == NULL)
		return -ENOMEM;

	*(u8 *)skb_push(skb, 1) = SHDLC_CONTROL_HEAD_S | (sframe_type << 3) | nr;

	r = shdlc->xmit_to_drv(shdlc->hdev, skb);

	kfree_skb(skb);

	return r;
}