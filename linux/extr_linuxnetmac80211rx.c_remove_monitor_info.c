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
struct sk_buff {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pskb_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  __pskb_trim (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void remove_monitor_info(struct sk_buff *skb,
				unsigned int present_fcs_len,
				unsigned int rtap_space)
{
	if (present_fcs_len)
		__pskb_trim(skb, skb->len - present_fcs_len);
	__pskb_pull(skb, rtap_space);
}