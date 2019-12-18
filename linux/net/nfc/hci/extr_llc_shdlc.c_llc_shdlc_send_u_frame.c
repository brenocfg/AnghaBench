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
typedef  enum uframe_modifier { ____Placeholder_uframe_modifier } uframe_modifier ;

/* Variables and functions */
 int SHDLC_CONTROL_HEAD_U ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int llc_shdlc_send_u_frame(struct llc_shdlc *shdlc,
				  struct sk_buff *skb,
				  enum uframe_modifier uframe_modifier)
{
	int r;

	pr_debug("uframe_modifier=%d\n", uframe_modifier);

	*(u8 *)skb_push(skb, 1) = SHDLC_CONTROL_HEAD_U | uframe_modifier;

	r = shdlc->xmit_to_drv(shdlc->hdev, skb);

	kfree_skb(skb);

	return r;
}