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
struct __kernel_timex {int status; } ;

/* Variables and functions */
 int STA_PLL ; 
 int STA_RONLY ; 
 int STA_UNSYNC ; 
 int /*<<< orphan*/  TIME64_MAX ; 
 int /*<<< orphan*/  TIME_OK ; 
 int /*<<< orphan*/  __ktime_get_real_seconds () ; 
 int /*<<< orphan*/  ntp_next_leap_sec ; 
 int /*<<< orphan*/  pps_reset_freq_interval () ; 
 int /*<<< orphan*/  time_reftime ; 
 int /*<<< orphan*/  time_state ; 
 int time_status ; 

__attribute__((used)) static inline void process_adj_status(const struct __kernel_timex *txc)
{
	if ((time_status & STA_PLL) && !(txc->status & STA_PLL)) {
		time_state = TIME_OK;
		time_status = STA_UNSYNC;
		ntp_next_leap_sec = TIME64_MAX;
		/* restart PPS frequency calibration */
		pps_reset_freq_interval();
	}

	/*
	 * If we turn on PLL adjustments then reset the
	 * reference time to current time.
	 */
	if (!(time_status & STA_PLL) && (txc->status & STA_PLL))
		time_reftime = __ktime_get_real_seconds();

	/* only set allowed bits */
	time_status &= STA_RONLY;
	time_status |= txc->status & ~STA_RONLY;
}