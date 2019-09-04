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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {unsigned int nr_frags; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ cxgbit_is_ofld_imm (struct sk_buff const*) ; 
 unsigned int cxgbit_sgl_len (unsigned int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 
 scalar_t__ skb_tail_pointer (struct sk_buff const*) ; 
 scalar_t__ skb_transport_header (struct sk_buff const*) ; 
 int skb_transport_offset (struct sk_buff const*) ; 

__attribute__((used)) static unsigned int cxgbit_calc_tx_flits_ofld(const struct sk_buff *skb)
{
	unsigned int flits, cnt;

	if (cxgbit_is_ofld_imm(skb))
		return DIV_ROUND_UP(skb->len, 8);
	flits = skb_transport_offset(skb) / 8;
	cnt = skb_shinfo(skb)->nr_frags;
	if (skb_tail_pointer(skb) != skb_transport_header(skb))
		cnt++;
	return flits + cxgbit_sgl_len(cnt);
}