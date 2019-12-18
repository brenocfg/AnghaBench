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

/* Variables and functions */
 struct sk_buff* __skb_clone (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_release_all (struct sk_buff*) ; 

struct sk_buff *skb_morph(struct sk_buff *dst, struct sk_buff *src)
{
	skb_release_all(dst);
	return __skb_clone(dst, src);
}