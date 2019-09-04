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
struct sk_buff {int len; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  dn_ack (struct sock*,struct sk_buff*,unsigned short) ; 
 unsigned short le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int dn_process_ack(struct sock *sk, struct sk_buff *skb, int oth)
{
	__le16 *ptr = (__le16 *)skb->data;
	int len = 0;
	unsigned short ack;

	if (skb->len < 2)
		return len;

	if ((ack = le16_to_cpu(*ptr)) & 0x8000) {
		skb_pull(skb, 2);
		ptr++;
		len += 2;
		if ((ack & 0x4000) == 0) {
			if (oth)
				ack ^= 0x2000;
			dn_ack(sk, skb, ack);
		}
	}

	if (skb->len < 2)
		return len;

	if ((ack = le16_to_cpu(*ptr)) & 0x8000) {
		skb_pull(skb, 2);
		len += 2;
		if ((ack & 0x4000) == 0) {
			if (oth)
				ack ^= 0x2000;
			dn_ack(sk, skb, ack);
		}
	}

	return len;
}