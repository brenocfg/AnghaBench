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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  select_queue_fallback_t ;

/* Variables and functions */

u16 dev_pick_tx_zero(struct net_device *dev, struct sk_buff *skb,
		     struct net_device *sb_dev,
		     select_queue_fallback_t fallback)
{
	return 0;
}