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
typedef  scalar_t__ u64 ;
struct timespec64 {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_2__ {scalar_t__ shift; scalar_t__ xtime_nsec; } ;
struct timekeeper {int skip_second_overflow; scalar_t__ tai_offset; int /*<<< orphan*/  wall_to_monotonic; scalar_t__ xtime_sec; TYPE_1__ tkr_mono; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 unsigned int TK_CLOCK_WAS_SET ; 
 int /*<<< orphan*/  __timekeeping_set_tai_offset (struct timekeeper*,scalar_t__) ; 
 int second_overflow (scalar_t__) ; 
 int /*<<< orphan*/  timespec64_sub (int /*<<< orphan*/ ,struct timespec64) ; 
 int /*<<< orphan*/  tk_set_wall_to_mono (struct timekeeper*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline unsigned int accumulate_nsecs_to_secs(struct timekeeper *tk)
{
	u64 nsecps = (u64)NSEC_PER_SEC << tk->tkr_mono.shift;
	unsigned int clock_set = 0;

	while (tk->tkr_mono.xtime_nsec >= nsecps) {
		int leap;

		tk->tkr_mono.xtime_nsec -= nsecps;
		tk->xtime_sec++;

		/*
		 * Skip NTP update if this second was accumulated before,
		 * i.e. xtime_nsec underflowed in timekeeping_adjust()
		 */
		if (unlikely(tk->skip_second_overflow)) {
			tk->skip_second_overflow = 0;
			continue;
		}

		/* Figure out if its a leap sec and apply if needed */
		leap = second_overflow(tk->xtime_sec);
		if (unlikely(leap)) {
			struct timespec64 ts;

			tk->xtime_sec += leap;

			ts.tv_sec = leap;
			ts.tv_nsec = 0;
			tk_set_wall_to_mono(tk,
				timespec64_sub(tk->wall_to_monotonic, ts));

			__timekeeping_set_tai_offset(tk, tk->tai_offset - leap);

			clock_set = TK_CLOCK_WAS_SET;
		}
	}
	return clock_set;
}