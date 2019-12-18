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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int get_tai () ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int set_tai (int) ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char **argv)
{
	int i, ret;

	ret = get_tai();
	printf("tai offset started at %i\n", ret);

	printf("Checking tai offsets can be properly set: ");
	fflush(stdout);
	for (i = 1; i <= 60; i++) {
		ret = set_tai(i);
		ret = get_tai();
		if (ret != i) {
			printf("[FAILED] expected: %i got %i\n", i, ret);
			return ksft_exit_fail();
		}
	}
	printf("[OK]\n");
	return ksft_exit_pass();
}