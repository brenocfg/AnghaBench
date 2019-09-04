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
struct mr_table {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool ipmr_forward_offloaded(struct sk_buff *skb, struct mr_table *mrt,
				   int in_vifi, int out_vifi)
{
	return false;
}