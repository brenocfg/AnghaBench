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
struct sk_buff {int len; int* data; } ;
typedef  int (* crc_func_t ) (int,int*,int) ;

/* Variables and functions */
 int EIO ; 
 int __swab16 (int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

int digital_skb_check_crc(struct sk_buff *skb, crc_func_t crc_func,
			  u16 crc_init, u8 bitwise_inv, u8 msb_first)
{
	int rc;
	u16 crc;

	if (skb->len <= 2)
		return -EIO;

	crc = crc_func(crc_init, skb->data, skb->len - 2);

	if (bitwise_inv)
		crc = ~crc;

	if (msb_first)
		crc = __swab16(crc);

	rc = (skb->data[skb->len - 2] - (crc & 0xFF)) +
	     (skb->data[skb->len - 1] - ((crc >> 8) & 0xFF));

	if (rc)
		return -EIO;

	skb_trim(skb, skb->len - 2);

	return 0;
}