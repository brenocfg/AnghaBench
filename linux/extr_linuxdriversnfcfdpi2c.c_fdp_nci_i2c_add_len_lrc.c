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
typedef  int u16 ;
struct sk_buff {int len; int* data; } ;

/* Variables and functions */
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 

__attribute__((used)) static void fdp_nci_i2c_add_len_lrc(struct sk_buff *skb)
{
	u8 lrc = 0;
	u16 len, i;

	/* Add length header */
	len = skb->len;
	*(u8 *)skb_push(skb, 1) = len & 0xff;
	*(u8 *)skb_push(skb, 1) = len >> 8;

	/* Compute and add lrc */
	for (i = 0; i < len + 2; i++)
		lrc ^= skb->data[i];

	skb_put_u8(skb, lrc);
}