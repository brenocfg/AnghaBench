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
typedef  scalar_t__ u64 ;
struct timecounter {scalar_t__ cycle_last; } ;
struct cyclecounter {int mult; scalar_t__ shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  read; } ;
struct hdac_stream {struct cyclecounter cc; struct timecounter tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKSOURCE_MASK (int) ; 
 int /*<<< orphan*/  azx_cc_read ; 
 int /*<<< orphan*/  timecounter_init (struct timecounter*,struct cyclecounter*,scalar_t__) ; 

__attribute__((used)) static void azx_timecounter_init(struct hdac_stream *azx_dev,
				 bool force, u64 last)
{
	struct timecounter *tc = &azx_dev->tc;
	struct cyclecounter *cc = &azx_dev->cc;
	u64 nsec;

	cc->read = azx_cc_read;
	cc->mask = CLOCKSOURCE_MASK(32);

	/*
	 * Converting from 24 MHz to ns means applying a 125/3 factor.
	 * To avoid any saturation issues in intermediate operations,
	 * the 125 factor is applied first. The division is applied
	 * last after reading the timecounter value.
	 * Applying the 1/3 factor as part of the multiplication
	 * requires at least 20 bits for a decent precision, however
	 * overflows occur after about 4 hours or less, not a option.
	 */

	cc->mult = 125; /* saturation after 195 years */
	cc->shift = 0;

	nsec = 0; /* audio time is elapsed time since trigger */
	timecounter_init(tc, cc, nsec);
	if (force) {
		/*
		 * force timecounter to use predefined value,
		 * used for synchronized starts
		 */
		tc->cycle_last = last;
	}
}