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
struct __sk_buff {int dummy; } ;

/* Variables and functions */
 int TC_ACT_OK ; 
 int /*<<< orphan*/  log_nth_level (struct __sk_buff*,int) ; 

int log_cgroup_id(struct __sk_buff *skb)
{
	/* Loop unroll can't be used here due to [1]. Unrolling manually.
	 * Number of calls should be in sync with NUM_CGROUP_LEVELS.
	 */
	log_nth_level(skb, 0);
	log_nth_level(skb, 1);
	log_nth_level(skb, 2);
	log_nth_level(skb, 3);

	return TC_ACT_OK;
}