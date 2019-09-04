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
 int /*<<< orphan*/  U_FRAME_UA ; 
 struct sk_buff* llc_shdlc_alloc_skb (struct llc_shdlc*,int /*<<< orphan*/ ) ; 
 int llc_shdlc_send_u_frame (struct llc_shdlc*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int llc_shdlc_connect_send_ua(struct llc_shdlc *shdlc)
{
	struct sk_buff *skb;

	pr_debug("\n");

	skb = llc_shdlc_alloc_skb(shdlc, 0);
	if (skb == NULL)
		return -ENOMEM;

	return llc_shdlc_send_u_frame(shdlc, skb, U_FRAME_UA);
}