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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int crc_ccitt (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 

__attribute__((used)) static void pn544_hci_i2c_add_len_crc(struct sk_buff *skb)
{
	u16 crc;
	int len;

	len = skb->len + 2;
	*(u8 *)skb_push(skb, 1) = len;

	crc = crc_ccitt(0xffff, skb->data, skb->len);
	crc = ~crc;
	skb_put_u8(skb, crc & 0xff);
	skb_put_u8(skb, crc >> 8);
}