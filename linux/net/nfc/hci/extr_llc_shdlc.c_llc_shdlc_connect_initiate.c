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
struct llc_shdlc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SHDLC_MAX_WINDOW ; 
 scalar_t__ SHDLC_SREJ_SUPPORT ; 
 int /*<<< orphan*/  U_FRAME_RSET ; 
 struct sk_buff* llc_shdlc_alloc_skb (struct llc_shdlc*,int) ; 
 int llc_shdlc_send_u_frame (struct llc_shdlc*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 

__attribute__((used)) static int llc_shdlc_connect_initiate(struct llc_shdlc *shdlc)
{
	struct sk_buff *skb;

	pr_debug("\n");

	skb = llc_shdlc_alloc_skb(shdlc, 2);
	if (skb == NULL)
		return -ENOMEM;

	skb_put_u8(skb, SHDLC_MAX_WINDOW);
	skb_put_u8(skb, SHDLC_SREJ_SUPPORT ? 1 : 0);

	return llc_shdlc_send_u_frame(shdlc, skb, U_FRAME_RSET);
}