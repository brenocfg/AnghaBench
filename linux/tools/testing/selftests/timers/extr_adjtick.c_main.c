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
struct timex {int tick; scalar_t__ freq; scalar_t__ offset; int /*<<< orphan*/  modes; } ;
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJ_FREQUENCY ; 
 int /*<<< orphan*/  ADJ_OFFSET ; 
 int /*<<< orphan*/  ADJ_TICK ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC_RAW ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  _SC_CLK_TCK ; 
 int /*<<< orphan*/  adjtimex (struct timex*) ; 
 scalar_t__ check_tick_adj (long) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int systick ; 

int main(int argv, char **argc)
{
	struct timespec raw;
	long tick, max, interval, err;
	struct timex tx1;

	err = 0;
	setbuf(stdout, NULL);

	if (clock_gettime(CLOCK_MONOTONIC_RAW, &raw)) {
		printf("ERR: NO CLOCK_MONOTONIC_RAW\n");
		return -1;
	}

	printf("Each iteration takes about 15 seconds\n");

	systick = sysconf(_SC_CLK_TCK);
	systick = USEC_PER_SEC/sysconf(_SC_CLK_TCK);
	max = systick/10; /* +/- 10% */
	interval = max/4; /* in 4 steps each side */

	for (tick = (systick - max); tick < (systick + max); tick += interval) {
		if (check_tick_adj(tick)) {
			err = 1;
			break;
		}
	}

	/* Reset things to zero */
	tx1.modes	 = ADJ_TICK;
	tx1.modes	|= ADJ_OFFSET;
	tx1.modes	|= ADJ_FREQUENCY;

	tx1.offset	 = 0;
	tx1.freq	 = 0;
	tx1.tick	 = systick;

	adjtimex(&tx1);

	if (err)
		return ksft_exit_fail();

	return ksft_exit_pass();
}