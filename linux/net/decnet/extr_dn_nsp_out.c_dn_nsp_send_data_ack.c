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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* dn_alloc_skb (struct sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_mk_ack_header (struct sock*,struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_nsp_send (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

void dn_nsp_send_data_ack(struct sock *sk)
{
	struct sk_buff *skb = NULL;

	if ((skb = dn_alloc_skb(sk, 9, GFP_ATOMIC)) == NULL)
		return;

	skb_reserve(skb, 9);
	dn_mk_ack_header(sk, skb, 0x04, 9, 0);
	dn_nsp_send(skb);
}