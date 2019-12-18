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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

struct sk_buff *nfc_alloc_recv_skb(unsigned int size, gfp_t gfp)
{
	struct sk_buff *skb;
	unsigned int total_size;

	total_size = size + 1;
	skb = alloc_skb(total_size, gfp);

	if (skb)
		skb_reserve(skb, 1);

	return skb;
}