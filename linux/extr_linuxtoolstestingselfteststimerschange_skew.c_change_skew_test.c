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
struct timex {int freq; int /*<<< orphan*/  modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJ_FREQUENCY ; 
 int adjtimex (struct timex*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int system (char*) ; 

int change_skew_test(int ppm)
{
	struct timex tx;
	int ret;

	tx.modes = ADJ_FREQUENCY;
	tx.freq = ppm << 16;

	ret = adjtimex(&tx);
	if (ret < 0) {
		printf("Error adjusting freq\n");
		return ret;
	}

	ret = system("./raw_skew");
	ret |= system("./inconsistency-check");
	ret |= system("./nanosleep");

	return ret;
}