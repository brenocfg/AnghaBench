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
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int __skb_datagram_iter (struct sk_buff const*,int,struct iov_iter*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_copy_to_iter ; 
 int /*<<< orphan*/  trace_skb_copy_datagram_iovec (struct sk_buff const*,int) ; 

int skb_copy_datagram_iter(const struct sk_buff *skb, int offset,
			   struct iov_iter *to, int len)
{
	trace_skb_copy_datagram_iovec(skb, len);
	return __skb_datagram_iter(skb, offset, to, len, false,
			simple_copy_to_iter, NULL);
}