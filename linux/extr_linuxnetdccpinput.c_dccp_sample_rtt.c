#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  long u32 ;
struct sock {int dummy; } ;
struct TYPE_3__ {int dccpor_elapsed_time; } ;
struct TYPE_4__ {TYPE_1__ dccps_options_received; } ;

/* Variables and functions */
 long DCCP_SANE_RTT_MAX ; 
 long DCCP_SANE_RTT_MIN ; 
 int /*<<< orphan*/  DCCP_WARN (char*,long) ; 
 TYPE_2__* dccp_sk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

u32 dccp_sample_rtt(struct sock *sk, long delta)
{
	/* dccpor_elapsed_time is either zeroed out or set and > 0 */
	delta -= dccp_sk(sk)->dccps_options_received.dccpor_elapsed_time * 10;

	if (unlikely(delta <= 0)) {
		DCCP_WARN("unusable RTT sample %ld, using min\n", delta);
		return DCCP_SANE_RTT_MIN;
	}
	if (unlikely(delta > DCCP_SANE_RTT_MAX)) {
		DCCP_WARN("RTT sample %ld too large, using max\n", delta);
		return DCCP_SANE_RTT_MAX;
	}

	return delta;
}