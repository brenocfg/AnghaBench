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
struct sk_buff {int dummy; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KSZ_EGRESS_TAG_LEN ; 
 struct sk_buff* ksz_common_rcv (struct sk_buff*,struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *ksz8795_rcv(struct sk_buff *skb, struct net_device *dev,
				  struct packet_type *pt)
{
	u8 *tag = skb_tail_pointer(skb) - KSZ_EGRESS_TAG_LEN;

	return ksz_common_rcv(skb, dev, tag[0] & 7, KSZ_EGRESS_TAG_LEN);
}