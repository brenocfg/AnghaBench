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

/* Variables and functions */
 int get_tz_dst () ; 
 int get_tz_min () ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int set_tz (int,int) ; 

int main(int argc, char **argv)
{
	int i, ret;
	int min, dst;

	min = get_tz_min();
	dst = get_tz_dst();
	printf("tz_minuteswest started at %i, dst at %i\n", min, dst);

	printf("Checking tz_minuteswest can be properly set: ");
	for (i = -15*60; i < 15*60; i += 30) {
		ret = set_tz(i, dst);
		ret = get_tz_min();
		if (ret != i) {
			printf("[FAILED] expected: %i got %i\n", i, ret);
			goto err;
		}
	}
	printf("[OK]\n");

	printf("Checking invalid tz_minuteswest values are caught: ");

	if (!set_tz(-15*60-1, dst)) {
		printf("[FAILED] %i didn't return failure!\n", -15*60-1);
		goto err;
	}

	if (!set_tz(15*60+1, dst)) {
		printf("[FAILED] %i didn't return failure!\n", 15*60+1);
		goto err;
	}

	if (!set_tz(-24*60, dst)) {
		printf("[FAILED] %i didn't return failure!\n", -24*60);
		goto err;
	}

	if (!set_tz(24*60, dst)) {
		printf("[FAILED] %i didn't return failure!\n", 24*60);
		goto err;
	}

	printf("[OK]\n");

	set_tz(min, dst);
	return ksft_exit_pass();

err:
	set_tz(min, dst);
	return ksft_exit_fail();
}