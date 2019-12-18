#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct sfb_skb_cb {int dummy; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  qdisc_cb_private_validate (struct sk_buff const*,int) ; 
 TYPE_1__* qdisc_skb_cb (struct sk_buff const*) ; 

__attribute__((used)) static inline struct sfb_skb_cb *sfb_skb_cb(const struct sk_buff *skb)
{
	qdisc_cb_private_validate(skb, sizeof(struct sfb_skb_cb));
	return (struct sfb_skb_cb *)qdisc_skb_cb(skb)->data;
}