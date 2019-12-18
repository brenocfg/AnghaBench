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
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int mqueue_lat_test () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char **argv)
{
	int ret;

	printf("Mqueue latency :                          ");
	fflush(stdout);

	ret = mqueue_lat_test();
	if (ret < 0) {
		printf("[FAILED]\n");
		return ksft_exit_fail();
	}
	printf("[OK]\n");
	return ksft_exit_pass();
}