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
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  enqueue_time; } ;

/* Variables and functions */
 TYPE_1__* get_cobalt_cb (struct sk_buff*) ; 

__attribute__((used)) static void cobalt_set_enqueue_time(struct sk_buff *skb,
				    ktime_t now)
{
	get_cobalt_cb(skb)->enqueue_time = now;
}