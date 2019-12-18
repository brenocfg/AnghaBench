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
struct sock {int /*<<< orphan*/  sk_rx_dst; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ dst_hold_safe (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct dst_entry* xchg (int /*<<< orphan*/ *,struct dst_entry*) ; 

bool udp_sk_rx_dst_set(struct sock *sk, struct dst_entry *dst)
{
	struct dst_entry *old;

	if (dst_hold_safe(dst)) {
		old = xchg(&sk->sk_rx_dst, dst);
		dst_release(old);
		return old != dst;
	}
	return false;
}