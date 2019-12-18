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
struct __sk_buff {scalar_t__ len; } ;

/* Variables and functions */

int combinations(volatile struct __sk_buff* skb)
{
	int ret = 0, i;

#pragma nounroll
	for (i = 0; i < 20; i++)
		if (skb->len)
			ret |= 1 << i;
	return ret;
}