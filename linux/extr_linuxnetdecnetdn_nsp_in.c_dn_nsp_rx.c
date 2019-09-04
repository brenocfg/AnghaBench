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
struct sk_buff {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_DECNET ; 
 int /*<<< orphan*/  NF_DN_LOCAL_IN ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_nsp_rx_packet ; 
 int /*<<< orphan*/  init_net ; 

int dn_nsp_rx(struct sk_buff *skb)
{
	return NF_HOOK(NFPROTO_DECNET, NF_DN_LOCAL_IN,
		       &init_net, NULL, skb, skb->dev, NULL,
		       dn_nsp_rx_packet);
}