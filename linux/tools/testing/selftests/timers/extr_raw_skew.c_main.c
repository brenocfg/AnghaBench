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
struct timex {int freq; scalar_t__ tick; scalar_t__ offset; scalar_t__ modes; } ;
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC_RAW ; 
 long long NSEC_PER_SEC ; 
 int /*<<< orphan*/  abs (int) ; 
 int /*<<< orphan*/  adjtimex (struct timex*) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 long long diff_timespec (struct timespec,struct timespec) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_monotonic_and_raw (struct timespec*,struct timespec*) ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int ksft_exit_skip (char*) ; 
 int llabs (long long) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long long shift_right (long long,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdout ; 

int main(int argv, char **argc)
{
	struct timespec mon, raw, start, end;
	long long delta1, delta2, interval, eppm, ppm;
	struct timex tx1, tx2;

	setbuf(stdout, NULL);

	if (clock_gettime(CLOCK_MONOTONIC_RAW, &raw)) {
		printf("ERR: NO CLOCK_MONOTONIC_RAW\n");
		return -1;
	}

	tx1.modes = 0;
	adjtimex(&tx1);
	get_monotonic_and_raw(&mon, &raw);
	start = mon;
	delta1 = diff_timespec(mon, raw);

	if (tx1.offset)
		printf("WARNING: ADJ_OFFSET in progress, this will cause inaccurate results\n");

	printf("Estimating clock drift: ");
	fflush(stdout);
	sleep(120);

	get_monotonic_and_raw(&mon, &raw);
	end = mon;
	tx2.modes = 0;
	adjtimex(&tx2);
	delta2 = diff_timespec(mon, raw);

	interval = diff_timespec(start, end);

	/* calculate measured ppm between MONOTONIC and MONOTONIC_RAW */
	eppm = ((delta2-delta1)*NSEC_PER_SEC)/interval;
	eppm = -eppm;
	printf("%lld.%i(est)", eppm/1000, abs((int)(eppm%1000)));

	/* Avg the two actual freq samples adjtimex gave us */
	ppm = (tx1.freq + tx2.freq) * 1000 / 2;
	ppm = (long long)tx1.freq * 1000;
	ppm = shift_right(ppm, 16);
	printf(" %lld.%i(act)", ppm/1000, abs((int)(ppm%1000)));

	if (llabs(eppm - ppm) > 1000) {
		if (tx1.offset || tx2.offset ||
		    tx1.freq != tx2.freq || tx1.tick != tx2.tick) {
			printf("	[SKIP]\n");
			return ksft_exit_skip("The clock was adjusted externally. Shutdown NTPd or other time sync daemons\n");
		}
		printf("	[FAILED]\n");
		return ksft_exit_fail();
	}
	printf("	[OK]\n");
	return  ksft_exit_pass();
}