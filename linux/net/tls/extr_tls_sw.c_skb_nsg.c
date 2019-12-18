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
 int __skb_nsg (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skb_nsg(struct sk_buff *skb, int offset, int len)
{
        return __skb_nsg(skb, offset, len, 0);
}