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
struct sk_buff {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ ) ; 

void __skb_warn_lro_forwarding(const struct sk_buff *skb)
{
	net_warn_ratelimited("%s: received packets cannot be forwarded while LRO is enabled\n",
			     skb->dev->name);
}