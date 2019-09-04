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
struct rfcomm_dev {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct sk_buff* alloc_skb (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_set_owner_w (struct sk_buff*,struct rfcomm_dev*) ; 

__attribute__((used)) static struct sk_buff *rfcomm_wmalloc(struct rfcomm_dev *dev, unsigned long size, gfp_t priority)
{
	struct sk_buff *skb = alloc_skb(size, priority);
	if (skb)
		rfcomm_set_owner_w(skb, dev);
	return skb;
}