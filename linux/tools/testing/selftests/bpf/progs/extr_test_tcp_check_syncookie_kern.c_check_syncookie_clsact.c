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
struct __sk_buff {scalar_t__ data_end; scalar_t__ data; } ;

/* Variables and functions */
 int TC_ACT_OK ; 
 int /*<<< orphan*/  check_syncookie (struct __sk_buff*,void*,void*) ; 

int check_syncookie_clsact(struct __sk_buff *skb)
{
	check_syncookie(skb, (void *)(long)skb->data,
			(void *)(long)skb->data_end);
	return TC_ACT_OK;
}