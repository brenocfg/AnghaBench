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
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  icsk_retransmits; } ;

/* Variables and functions */
 unsigned int const TCP_RTO_MAX ; 
 unsigned int TCP_RTO_MIN ; 
 unsigned int ilog2 (unsigned int const) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 unsigned int jiffies_to_msecs (unsigned int) ; 
 scalar_t__ likely (int) ; 
 unsigned int tcp_retransmit_stamp (struct sock*) ; 
 int /*<<< orphan*/  tcp_sk (struct sock*) ; 
 unsigned int tcp_time_stamp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool retransmits_timed_out(struct sock *sk,
				  unsigned int boundary,
				  unsigned int timeout)
{
	const unsigned int rto_base = TCP_RTO_MIN;
	unsigned int linear_backoff_thresh, start_ts;

	if (!inet_csk(sk)->icsk_retransmits)
		return false;

	start_ts = tcp_retransmit_stamp(sk);
	if (!start_ts)
		return false;

	if (likely(timeout == 0)) {
		linear_backoff_thresh = ilog2(TCP_RTO_MAX/rto_base);

		if (boundary <= linear_backoff_thresh)
			timeout = ((2 << boundary) - 1) * rto_base;
		else
			timeout = ((2 << linear_backoff_thresh) - 1) * rto_base +
				(boundary - linear_backoff_thresh) * TCP_RTO_MAX;
		timeout = jiffies_to_msecs(timeout);
	}
	return (tcp_time_stamp(tcp_sk(sk)) - start_ts) >= timeout;
}