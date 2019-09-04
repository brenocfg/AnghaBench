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
struct sk_buff {scalar_t__ tstamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  netstamp_needed_key ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void net_timestamp_set(struct sk_buff *skb)
{
	skb->tstamp = 0;
	if (static_branch_unlikely(&netstamp_needed_key))
		__net_timestamp(skb);
}