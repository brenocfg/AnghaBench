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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct tcp_sock {int mss_cache; int /*<<< orphan*/  rate_interval_us; int /*<<< orphan*/  rate_delivered; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  do_div (int,scalar_t__) ; 

__attribute__((used)) static u64 tcp_compute_delivery_rate(const struct tcp_sock *tp)
{
	u32 rate = READ_ONCE(tp->rate_delivered);
	u32 intv = READ_ONCE(tp->rate_interval_us);
	u64 rate64 = 0;

	if (rate && intv) {
		rate64 = (u64)rate * tp->mss_cache * USEC_PER_SEC;
		do_div(rate64, intv);
	}
	return rate64;
}