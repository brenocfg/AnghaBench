#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
struct sock {int dummy; } ;
struct TYPE_2__ {unsigned int mss_cache; } ;

/* Variables and functions */
 unsigned int BBR_SCALE ; 
 unsigned int BW_SCALE ; 
 unsigned int USEC_PER_SEC ; 
 unsigned int tcp_mss_to_mtu (struct sock*,unsigned int) ; 
 int /*<<< orphan*/  tcp_needs_internal_pacing (struct sock*) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 

__attribute__((used)) static u64 bbr_rate_bytes_per_sec(struct sock *sk, u64 rate, int gain)
{
	unsigned int mss = tcp_sk(sk)->mss_cache;

	if (!tcp_needs_internal_pacing(sk))
		mss = tcp_mss_to_mtu(sk, mss);
	rate *= mss;
	rate *= gain;
	rate >>= BBR_SCALE;
	rate *= USEC_PER_SEC;
	return rate >> BW_SCALE;
}