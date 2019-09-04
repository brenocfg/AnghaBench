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

/* Variables and functions */
 int __skb_trim_rcsum (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int bpf_skb_trim_rcsum(struct sk_buff *skb, unsigned int new_len)
{
	return __skb_trim_rcsum(skb, new_len);
}