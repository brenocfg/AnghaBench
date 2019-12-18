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
struct inet_timewait_sock {int tw_kill; int /*<<< orphan*/  tw_timer; TYPE_1__* tw_dr; } ;
struct TYPE_2__ {int /*<<< orphan*/  tw_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mod_timer_pending (int /*<<< orphan*/ *,scalar_t__) ; 

void __inet_twsk_schedule(struct inet_timewait_sock *tw, int timeo, bool rearm)
{
	/* timeout := RTO * 3.5
	 *
	 * 3.5 = 1+2+0.5 to wait for two retransmits.
	 *
	 * RATIONALE: if FIN arrived and we entered TIME-WAIT state,
	 * our ACK acking that FIN can be lost. If N subsequent retransmitted
	 * FINs (or previous seqments) are lost (probability of such event
	 * is p^(N+1), where p is probability to lose single packet and
	 * time to detect the loss is about RTO*(2^N - 1) with exponential
	 * backoff). Normal timewait length is calculated so, that we
	 * waited at least for one retransmitted FIN (maximal RTO is 120sec).
	 * [ BTW Linux. following BSD, violates this requirement waiting
	 *   only for 60sec, we should wait at least for 240 secs.
	 *   Well, 240 consumes too much of resources 8)
	 * ]
	 * This interval is not reduced to catch old duplicate and
	 * responces to our wandering segments living for two MSLs.
	 * However, if we use PAWS to detect
	 * old duplicates, we can reduce the interval to bounds required
	 * by RTO, rather than MSL. So, if peer understands PAWS, we
	 * kill tw bucket after 3.5*RTO (it is important that this number
	 * is greater than TS tick!) and detect old duplicates with help
	 * of PAWS.
	 */

	tw->tw_kill = timeo <= 4*HZ;
	if (!rearm) {
		BUG_ON(mod_timer(&tw->tw_timer, jiffies + timeo));
		atomic_inc(&tw->tw_dr->tw_count);
	} else {
		mod_timer_pending(&tw->tw_timer, jiffies + timeo);
	}
}