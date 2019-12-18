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
struct TYPE_2__ {long long tv_sec; long long tv_usec; } ;
struct timex {TYPE_1__ time; int /*<<< orphan*/  modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJ_NANO ; 
 int /*<<< orphan*/  ADJ_SETOFFSET ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 long long NSEC_PER_SEC ; 
 long long USEC_PER_SEC ; 
 int clock_adjtime (int /*<<< orphan*/ ,struct timex*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int set_offset(long long offset, int use_nano)
{
	struct timex tmx = {};
	int ret;

	tmx.modes = ADJ_SETOFFSET;
	if (use_nano) {
		tmx.modes |= ADJ_NANO;

		tmx.time.tv_sec = offset / NSEC_PER_SEC;
		tmx.time.tv_usec = offset % NSEC_PER_SEC;

		if (offset < 0 && tmx.time.tv_usec) {
			tmx.time.tv_sec -= 1;
			tmx.time.tv_usec += NSEC_PER_SEC;
		}
	} else {
		tmx.time.tv_sec = offset / USEC_PER_SEC;
		tmx.time.tv_usec = offset % USEC_PER_SEC;

		if (offset < 0 && tmx.time.tv_usec) {
			tmx.time.tv_sec -= 1;
			tmx.time.tv_usec += USEC_PER_SEC;
		}
	}

	ret = clock_adjtime(CLOCK_REALTIME, &tmx);
	if (ret < 0) {
		printf("(sec: %ld  usec: %ld) ", tmx.time.tv_sec, tmx.time.tv_usec);
		printf("[FAIL]\n");
		return -1;
	}
	return 0;
}