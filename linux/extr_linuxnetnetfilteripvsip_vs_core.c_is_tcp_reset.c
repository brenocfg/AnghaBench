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
struct tcphdr {int rst; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  _tcph ;

/* Variables and functions */
 struct tcphdr* skb_header_pointer (struct sk_buff const*,int,int,struct tcphdr*) ; 

__attribute__((used)) static inline int is_tcp_reset(const struct sk_buff *skb, int nh_len)
{
	struct tcphdr _tcph, *th;

	th = skb_header_pointer(skb, nh_len, sizeof(_tcph), &_tcph);
	if (th == NULL)
		return 0;
	return th->rst;
}