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
 scalar_t__ skb_is_err_queue (struct sk_buff const*) ; 

__attribute__((used)) static bool skb_is_swtx_tstamp(const struct sk_buff *skb, int false_tstamp)
{
	return skb->tstamp && !false_tstamp && skb_is_err_queue(skb);
}