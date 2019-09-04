#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  enqueue_time; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 TYPE_2__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  codel_get_time () ; 

__attribute__((used)) static void ieee80211_set_skb_enqueue_time(struct sk_buff *skb)
{
	IEEE80211_SKB_CB(skb)->control.enqueue_time = codel_get_time();
}