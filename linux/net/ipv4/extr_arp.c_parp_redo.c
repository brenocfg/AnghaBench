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
struct sk_buff {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  arp_process (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parp_redo(struct sk_buff *skb)
{
	arp_process(dev_net(skb->dev), NULL, skb);
}