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
struct xtm {int weekday; int monthday; } ;
struct xt_time_info {int flags; scalar_t__ date_start; scalar_t__ date_stop; unsigned int daytime_start; unsigned int daytime_stop; int weekdays_match; int monthdays_match; } ;
struct xt_action_param {struct xt_time_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
typedef  scalar_t__ s64 ;
struct TYPE_2__ {int tz_minuteswest; } ;

/* Variables and functions */
 scalar_t__ SECONDS_PER_DAY ; 
 int XT_TIME_ALL_MONTHDAYS ; 
 int XT_TIME_CONTIGUOUS ; 
 int XT_TIME_LOCAL_TZ ; 
 scalar_t__ get_seconds () ; 
 unsigned int localtime_1 (struct xtm*,scalar_t__) ; 
 int /*<<< orphan*/  localtime_2 (struct xtm*,scalar_t__) ; 
 int /*<<< orphan*/  localtime_3 (struct xtm*,scalar_t__) ; 
 TYPE_1__ sys_tz ; 

__attribute__((used)) static bool
time_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_time_info *info = par->matchinfo;
	unsigned int packet_time;
	struct xtm current_time;
	s64 stamp;

	/*
	 * We need real time here, but we can neither use skb->tstamp
	 * nor __net_timestamp().
	 *
	 * skb->tstamp and skb->skb_mstamp_ns overlap, however, they
	 * use different clock types (real vs monotonic).
	 *
	 * Suppose you have two rules:
	 *	1. match before 13:00
	 *	2. match after 13:00
	 *
	 * If you match against processing time (get_seconds) it
	 * may happen that the same packet matches both rules if
	 * it arrived at the right moment before 13:00, so it would be
	 * better to check skb->tstamp and set it via __net_timestamp()
	 * if needed.  This however breaks outgoing packets tx timestamp,
	 * and causes them to get delayed forever by fq packet scheduler.
	 */
	stamp = get_seconds();

	if (info->flags & XT_TIME_LOCAL_TZ)
		/* Adjust for local timezone */
		stamp -= 60 * sys_tz.tz_minuteswest;

	/*
	 * xt_time will match when _all_ of the following hold:
	 *   - 'now' is in the global time range date_start..date_end
	 *   - 'now' is in the monthday mask
	 *   - 'now' is in the weekday mask
	 *   - 'now' is in the daytime range time_start..time_end
	 * (and by default, libxt_time will set these so as to match)
	 */

	if (stamp < info->date_start || stamp > info->date_stop)
		return false;

	packet_time = localtime_1(&current_time, stamp);

	if (info->daytime_start < info->daytime_stop) {
		if (packet_time < info->daytime_start ||
		    packet_time > info->daytime_stop)
			return false;
	} else {
		if (packet_time < info->daytime_start &&
		    packet_time > info->daytime_stop)
			return false;

		/** if user asked to ignore 'next day', then e.g.
		 *  '1 PM Wed, August 1st' should be treated
		 *  like 'Tue 1 PM July 31st'.
		 *
		 * This also causes
		 * 'Monday, "23:00 to 01:00", to match for 2 hours, starting
		 * Monday 23:00 to Tuesday 01:00.
		 */
		if ((info->flags & XT_TIME_CONTIGUOUS) &&
		     packet_time <= info->daytime_stop)
			stamp -= SECONDS_PER_DAY;
	}

	localtime_2(&current_time, stamp);

	if (!(info->weekdays_match & (1 << current_time.weekday)))
		return false;

	/* Do not spend time computing monthday if all days match anyway */
	if (info->monthdays_match != XT_TIME_ALL_MONTHDAYS) {
		localtime_3(&current_time, stamp);
		if (!(info->monthdays_match & (1 << current_time.monthday)))
			return false;
	}

	return true;
}