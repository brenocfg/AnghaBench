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
struct sk_buff {scalar_t__ cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  enqueue_time; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
typedef  int /*<<< orphan*/  codel_time_t ;

/* Variables and functions */

__attribute__((used)) static codel_time_t codel_skb_time_func(const struct sk_buff *skb)
{
	const struct ieee80211_tx_info *info;

	info = (const struct ieee80211_tx_info *)skb->cb;
	return info->control.enqueue_time;
}