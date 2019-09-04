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
typedef  scalar_t__ time_t ;
struct TYPE_2__ {long tv_usec; scalar_t__ tv_sec; } ;
struct timex {int modes; long offset; int status; int precision; int tolerance; TYPE_1__ time; int /*<<< orphan*/  tai; int /*<<< orphan*/  tick; int /*<<< orphan*/  constant; int /*<<< orphan*/  esterror; int /*<<< orphan*/  maxerror; void* freq; } ;
struct timespec64 {scalar_t__ tv_sec; long tv_nsec; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int ADJ_ADJTIME ; 
 int ADJ_OFFSET_READONLY ; 
 int MAXFREQ_SCALED ; 
 long NSEC_PER_USEC ; 
 int NTP_INTERVAL_FREQ ; 
 int /*<<< orphan*/  NTP_SCALE_SHIFT ; 
 int PPM_SCALE ; 
 int PPM_SCALE_INV ; 
 int PPM_SCALE_INV_SHIFT ; 
 int STA_DEL ; 
 int STA_INS ; 
 int STA_NANO ; 
 int TIME_DEL ; 
 int TIME_ERROR ; 
 int TIME_INS ; 
 int TIME_OOP ; 
 int TIME_WAIT ; 
 scalar_t__ is_error_status (int) ; 
 scalar_t__ ntp_next_leap_sec ; 
 int /*<<< orphan*/  ntp_update_frequency () ; 
 int /*<<< orphan*/  pps_fill_timex (struct timex*) ; 
 int /*<<< orphan*/  process_adjtimex_modes (struct timex*,int /*<<< orphan*/ *) ; 
 void* shift_right (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_usec ; 
 long time_adjust ; 
 int /*<<< orphan*/  time_constant ; 
 int /*<<< orphan*/  time_esterror ; 
 int time_freq ; 
 int /*<<< orphan*/  time_maxerror ; 
 int time_offset ; 
 int time_state ; 
 int time_status ; 
 scalar_t__ unlikely (int) ; 

int __do_adjtimex(struct timex *txc, const struct timespec64 *ts, s32 *time_tai)
{
	int result;

	if (txc->modes & ADJ_ADJTIME) {
		long save_adjust = time_adjust;

		if (!(txc->modes & ADJ_OFFSET_READONLY)) {
			/* adjtime() is independent from ntp_adjtime() */
			time_adjust = txc->offset;
			ntp_update_frequency();
		}
		txc->offset = save_adjust;
	} else {

		/* If there are input parameters, then process them: */
		if (txc->modes)
			process_adjtimex_modes(txc, time_tai);

		txc->offset = shift_right(time_offset * NTP_INTERVAL_FREQ,
				  NTP_SCALE_SHIFT);
		if (!(time_status & STA_NANO))
			txc->offset /= NSEC_PER_USEC;
	}

	result = time_state;	/* mostly `TIME_OK' */
	/* check for errors */
	if (is_error_status(time_status))
		result = TIME_ERROR;

	txc->freq	   = shift_right((time_freq >> PPM_SCALE_INV_SHIFT) *
					 PPM_SCALE_INV, NTP_SCALE_SHIFT);
	txc->maxerror	   = time_maxerror;
	txc->esterror	   = time_esterror;
	txc->status	   = time_status;
	txc->constant	   = time_constant;
	txc->precision	   = 1;
	txc->tolerance	   = MAXFREQ_SCALED / PPM_SCALE;
	txc->tick	   = tick_usec;
	txc->tai	   = *time_tai;

	/* fill PPS status fields */
	pps_fill_timex(txc);

	txc->time.tv_sec = (time_t)ts->tv_sec;
	txc->time.tv_usec = ts->tv_nsec;
	if (!(time_status & STA_NANO))
		txc->time.tv_usec /= NSEC_PER_USEC;

	/* Handle leapsec adjustments */
	if (unlikely(ts->tv_sec >= ntp_next_leap_sec)) {
		if ((time_state == TIME_INS) && (time_status & STA_INS)) {
			result = TIME_OOP;
			txc->tai++;
			txc->time.tv_sec--;
		}
		if ((time_state == TIME_DEL) && (time_status & STA_DEL)) {
			result = TIME_WAIT;
			txc->tai--;
			txc->time.tv_sec++;
		}
		if ((time_state == TIME_OOP) &&
					(ts->tv_sec == ntp_next_leap_sec)) {
			result = TIME_WAIT;
		}
	}

	return result;
}