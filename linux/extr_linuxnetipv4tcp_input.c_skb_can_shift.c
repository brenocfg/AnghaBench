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
 int /*<<< orphan*/  skb_headlen (struct sk_buff const*) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff const*) ; 

__attribute__((used)) static int skb_can_shift(const struct sk_buff *skb)
{
	return !skb_headlen(skb) && skb_is_nonlinear(skb);
}