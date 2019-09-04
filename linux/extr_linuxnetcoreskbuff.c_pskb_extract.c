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
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ pskb_carve (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pskb_trim (struct sk_buff*,int) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 

struct sk_buff *pskb_extract(struct sk_buff *skb, int off,
			     int to_copy, gfp_t gfp)
{
	struct sk_buff  *clone = skb_clone(skb, gfp);

	if (!clone)
		return NULL;

	if (pskb_carve(clone, off, gfp) < 0 ||
	    pskb_trim(clone, to_copy)) {
		kfree_skb(clone);
		return NULL;
	}
	return clone;
}