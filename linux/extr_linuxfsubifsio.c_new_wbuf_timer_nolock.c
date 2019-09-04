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
struct ubifs_wbuf {int /*<<< orphan*/  timer; int /*<<< orphan*/  jhead; scalar_t__ no_timer; } ;
struct ubifs_info {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 unsigned long long NSEC_PER_MSEC ; 
 unsigned long long ULONG_MAX ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  dbg_io (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_jhead (int /*<<< orphan*/ ) ; 
 int dirty_writeback_interval ; 
 int /*<<< orphan*/  div_u64 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start_range_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_to_ktime (int) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 

__attribute__((used)) static void new_wbuf_timer_nolock(struct ubifs_info *c, struct ubifs_wbuf *wbuf)
{
	ktime_t softlimit = ms_to_ktime(dirty_writeback_interval * 10);
	unsigned long long delta = dirty_writeback_interval;

	/* centi to milli, milli to nano, then 10% */
	delta *= 10ULL * NSEC_PER_MSEC / 10ULL;

	ubifs_assert(c, !hrtimer_active(&wbuf->timer));
	ubifs_assert(c, delta <= ULONG_MAX);

	if (wbuf->no_timer)
		return;
	dbg_io("set timer for jhead %s, %llu-%llu millisecs",
	       dbg_jhead(wbuf->jhead),
	       div_u64(ktime_to_ns(softlimit), USEC_PER_SEC),
	       div_u64(ktime_to_ns(softlimit) + delta, USEC_PER_SEC));
	hrtimer_start_range_ns(&wbuf->timer, softlimit, delta,
			       HRTIMER_MODE_REL);
}