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
struct tcp_sock {int advmss; } ;
struct sock {int dummy; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 struct dst_entry* __sk_dst_get (struct sock*) ; 
 unsigned int dst_metric_advmss (struct dst_entry const*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static __u16 tcp_advertise_mss(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	const struct dst_entry *dst = __sk_dst_get(sk);
	int mss = tp->advmss;

	if (dst) {
		unsigned int metric = dst_metric_advmss(dst);

		if (metric < mss) {
			mss = metric;
			tp->advmss = mss;
		}
	}

	return (__u16)mss;
}