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
struct TYPE_2__ {long tv_sec; long tv_usec; } ;
struct timex {TYPE_1__ time; int /*<<< orphan*/  modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJ_NANO ; 
 int /*<<< orphan*/  ADJ_SETOFFSET ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int clock_adjtime (int /*<<< orphan*/ ,struct timex*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int set_bad_offset(long sec, long usec, int use_nano)
{
	struct timex tmx = {};
	int ret;

	tmx.modes = ADJ_SETOFFSET;
	if (use_nano)
		tmx.modes |= ADJ_NANO;

	tmx.time.tv_sec = sec;
	tmx.time.tv_usec = usec;
	ret = clock_adjtime(CLOCK_REALTIME, &tmx);
	if (ret >= 0) {
		printf("Invalid (sec: %ld  usec: %ld) did not fail! ", tmx.time.tv_sec, tmx.time.tv_usec);
		printf("[FAIL]\n");
		return -1;
	}
	return 0;
}