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
struct timer_list {int dummy; } ;
struct net_rate_estimator {int last_bytes; int ewma_log; int intvl_log; int avbps; int avpps; scalar_t__ next_jiffies; int /*<<< orphan*/  timer; scalar_t__ last_packets; int /*<<< orphan*/  seq; } ;
struct gnet_stats_basic_packed {int bytes; scalar_t__ packets; } ;

/* Variables and functions */
 int HZ ; 
 struct net_rate_estimator* est ; 
 int /*<<< orphan*/  est_fetch_counters (struct net_rate_estimator*,struct gnet_stats_basic_packed*) ; 
 struct net_rate_estimator* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  time_after_eq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  timer ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void est_timer(struct timer_list *t)
{
	struct net_rate_estimator *est = from_timer(est, t, timer);
	struct gnet_stats_basic_packed b;
	u64 rate, brate;

	est_fetch_counters(est, &b);
	brate = (b.bytes - est->last_bytes) << (10 - est->ewma_log - est->intvl_log);
	brate -= (est->avbps >> est->ewma_log);

	rate = (u64)(b.packets - est->last_packets) << (10 - est->ewma_log - est->intvl_log);
	rate -= (est->avpps >> est->ewma_log);

	write_seqcount_begin(&est->seq);
	est->avbps += brate;
	est->avpps += rate;
	write_seqcount_end(&est->seq);

	est->last_bytes = b.bytes;
	est->last_packets = b.packets;

	est->next_jiffies += ((HZ/4) << est->intvl_log);

	if (unlikely(time_after_eq(jiffies, est->next_jiffies))) {
		/* Ouch... timer was delayed. */
		est->next_jiffies = jiffies + 1;
	}
	mod_timer(&est->timer, est->next_jiffies);
}