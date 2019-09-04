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
struct sk_buff {int data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_fpa_free (int,int,int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cvm_oct_fill_hw_skbuff(int pool, int size, int elements)
{
	int freed = elements;

	while (freed) {
		struct sk_buff *skb = dev_alloc_skb(size + 256);

		if (unlikely(!skb))
			break;
		skb_reserve(skb, 256 - (((unsigned long)skb->data) & 0x7f));
		*(struct sk_buff **)(skb->data - sizeof(void *)) = skb;
		cvmx_fpa_free(skb->data, pool, size / 128);
		freed--;
	}
	return elements - freed;
}