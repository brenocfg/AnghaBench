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
 int skb_ensure_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static inline int __bpf_try_make_writable(struct sk_buff *skb,
					  unsigned int write_len)
{
	return skb_ensure_writable(skb, write_len);
}