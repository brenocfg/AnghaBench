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
 int /*<<< orphan*/  lookup_no_release (struct __sk_buff*) ; 

int bpf_sk_lookup_test5(struct __sk_buff *skb)
{
	lookup_no_release(skb);
	return 0;
}