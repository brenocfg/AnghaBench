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
 int CLOCK_HWSPECIFIC ; 
 int CLOCK_PROCESS_CPUTIME_ID ; 
 int CLOCK_REALTIME ; 
 int CLOCK_THREAD_CPUTIME_ID ; 
 int NR_CLOCKIDS ; 
 int NSEC_PER_SEC ; 
 int UNSUPPORTED ; 
 char* clockstring (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int nanosleep_test (int,long long) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char **argv)
{
	long long length;
	int clockid, ret;

	for (clockid = CLOCK_REALTIME; clockid < NR_CLOCKIDS; clockid++) {

		/* Skip cputime clockids since nanosleep won't increment cputime */
		if (clockid == CLOCK_PROCESS_CPUTIME_ID ||
				clockid == CLOCK_THREAD_CPUTIME_ID ||
				clockid == CLOCK_HWSPECIFIC)
			continue;

		printf("Nanosleep %-31s ", clockstring(clockid));
		fflush(stdout);

		length = 10;
		while (length <= (NSEC_PER_SEC * 10)) {
			ret = nanosleep_test(clockid, length);
			if (ret == UNSUPPORTED) {
				printf("[UNSUPPORTED]\n");
				goto next;
			}
			if (ret < 0) {
				printf("[FAILED]\n");
				return ksft_exit_fail();
			}
			length *= 100;
		}
		printf("[OK]\n");
next:
		ret = 0;
	}
	return ksft_exit_pass();
}