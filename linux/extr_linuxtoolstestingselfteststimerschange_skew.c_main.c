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
struct timex {scalar_t__ offset; int /*<<< orphan*/  modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJ_FREQUENCY ; 
 int /*<<< orphan*/  ADJ_OFFSET ; 
 int adjtimex (struct timex*) ; 
 int change_skew_test (int) ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int system (char*) ; 

int main(int argv, char **argc)
{
	struct timex tx;
	int i, ret;

	int ppm[5] = {0, 250, 500, -250, -500};

	/* Kill ntpd */
	ret = system("killall -9 ntpd");

	/* Make sure there's no offset adjustment going on */
	tx.modes = ADJ_OFFSET;
	tx.offset = 0;
	ret = adjtimex(&tx);

	if (ret < 0) {
		printf("Maybe you're not running as root?\n");
		return -1;
	}

	for (i = 0; i < 5; i++) {
		printf("Using %i ppm adjustment\n", ppm[i]);
		ret = change_skew_test(ppm[i]);
		if (ret)
			break;
	}

	/* Set things back */
	tx.modes = ADJ_FREQUENCY;
	tx.offset = 0;
	adjtimex(&tx);

	if (ret) {
		printf("[FAIL]");
		return ksft_exit_fail();
	}
	printf("[OK]");
	return ksft_exit_pass();
}