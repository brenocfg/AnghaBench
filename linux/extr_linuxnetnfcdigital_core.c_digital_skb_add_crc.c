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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  int (* crc_func_t ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int __fswab16 (int) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 

void digital_skb_add_crc(struct sk_buff *skb, crc_func_t crc_func, u16 init,
			 u8 bitwise_inv, u8 msb_first)
{
	u16 crc;

	crc = crc_func(init, skb->data, skb->len);

	if (bitwise_inv)
		crc = ~crc;

	if (msb_first)
		crc = __fswab16(crc);

	skb_put_u8(skb, crc & 0xFF);
	skb_put_u8(skb, (crc >> 8) & 0xFF);
}