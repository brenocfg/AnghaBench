#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ spins; scalar_t__ delays; int cur_delay; int /*<<< orphan*/  func; int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ SpinDelayStatus ;

/* Variables and functions */
 double MAX_DELAY_USEC ; 
 scalar_t__ MAX_RANDOM_VALUE ; 
 void* MIN_DELAY_USEC ; 
 scalar_t__ NUM_DELAYS ; 
 int /*<<< orphan*/  SPIN_DELAY () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pg_usleep (int) ; 
 scalar_t__ random () ; 
 int /*<<< orphan*/  s_lock_stuck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spins_per_delay ; 
 int /*<<< orphan*/  stdout ; 

void
perform_spin_delay(SpinDelayStatus *status)
{
	/* CPU-specific delay each time through the loop */
	SPIN_DELAY();

	/* Block the process every spins_per_delay tries */
	if (++(status->spins) >= spins_per_delay)
	{
		if (++(status->delays) > NUM_DELAYS)
			s_lock_stuck(status->file, status->line, status->func);

		if (status->cur_delay == 0) /* first time to delay? */
			status->cur_delay = MIN_DELAY_USEC;

		pg_usleep(status->cur_delay);

#if defined(S_LOCK_TEST)
		fprintf(stdout, "*");
		fflush(stdout);
#endif

		/* increase delay by a random fraction between 1X and 2X */
		status->cur_delay += (int) (status->cur_delay *
									((double) random() / (double) MAX_RANDOM_VALUE) + 0.5);
		/* wrap back to minimum delay when max is exceeded */
		if (status->cur_delay > MAX_DELAY_USEC)
			status->cur_delay = MIN_DELAY_USEC;

		status->spins = 0;
	}
}