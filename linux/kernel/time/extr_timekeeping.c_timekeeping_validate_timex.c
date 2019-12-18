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
struct TYPE_2__ {scalar_t__ tv_usec; } ;
struct __kernel_timex {int modes; int tick; int freq; TYPE_1__ time; } ;

/* Variables and functions */
 int ADJ_ADJTIME ; 
 int ADJ_FREQUENCY ; 
 int ADJ_NANO ; 
 int ADJ_OFFSET_READONLY ; 
 int ADJ_OFFSET_SINGLESHOT ; 
 int ADJ_SETOFFSET ; 
 int ADJ_TICK ; 
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  CAP_SYS_TIME ; 
 int EINVAL ; 
 int EPERM ; 
 int LLONG_MAX ; 
 int LLONG_MIN ; 
 scalar_t__ NSEC_PER_SEC ; 
 int PPM_SCALE ; 
 scalar_t__ USEC_PER_SEC ; 
 int USER_HZ ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int timekeeping_validate_timex(const struct __kernel_timex *txc)
{
	if (txc->modes & ADJ_ADJTIME) {
		/* singleshot must not be used with any other mode bits */
		if (!(txc->modes & ADJ_OFFSET_SINGLESHOT))
			return -EINVAL;
		if (!(txc->modes & ADJ_OFFSET_READONLY) &&
		    !capable(CAP_SYS_TIME))
			return -EPERM;
	} else {
		/* In order to modify anything, you gotta be super-user! */
		if (txc->modes && !capable(CAP_SYS_TIME))
			return -EPERM;
		/*
		 * if the quartz is off by more than 10% then
		 * something is VERY wrong!
		 */
		if (txc->modes & ADJ_TICK &&
		    (txc->tick <  900000/USER_HZ ||
		     txc->tick > 1100000/USER_HZ))
			return -EINVAL;
	}

	if (txc->modes & ADJ_SETOFFSET) {
		/* In order to inject time, you gotta be super-user! */
		if (!capable(CAP_SYS_TIME))
			return -EPERM;

		/*
		 * Validate if a timespec/timeval used to inject a time
		 * offset is valid.  Offsets can be postive or negative, so
		 * we don't check tv_sec. The value of the timeval/timespec
		 * is the sum of its fields,but *NOTE*:
		 * The field tv_usec/tv_nsec must always be non-negative and
		 * we can't have more nanoseconds/microseconds than a second.
		 */
		if (txc->time.tv_usec < 0)
			return -EINVAL;

		if (txc->modes & ADJ_NANO) {
			if (txc->time.tv_usec >= NSEC_PER_SEC)
				return -EINVAL;
		} else {
			if (txc->time.tv_usec >= USEC_PER_SEC)
				return -EINVAL;
		}
	}

	/*
	 * Check for potential multiplication overflows that can
	 * only happen on 64-bit systems:
	 */
	if ((txc->modes & ADJ_FREQUENCY) && (BITS_PER_LONG == 64)) {
		if (LLONG_MIN / PPM_SCALE > txc->freq)
			return -EINVAL;
		if (LLONG_MAX / PPM_SCALE < txc->freq)
			return -EINVAL;
	}

	return 0;
}