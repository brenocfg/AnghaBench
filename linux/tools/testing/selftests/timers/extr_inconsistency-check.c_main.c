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
struct timespec {int dummy; } ;

/* Variables and functions */
 int CLOCK_HWSPECIFIC ; 
 int CLOCK_REALTIME ; 
 int NR_CLOCKIDS ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_gettime (int,struct timespec*) ; 
 char* clockstring (int) ; 
 scalar_t__ consistency_test (int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char *argv[])
{
	int clockid, opt;
	int userclock = CLOCK_REALTIME;
	int maxclocks = NR_CLOCKIDS;
	int runtime = 10;
	struct timespec ts;

	/* Process arguments */
	while ((opt = getopt(argc, argv, "t:c:")) != -1) {
		switch (opt) {
		case 't':
			runtime = atoi(optarg);
			break;
		case 'c':
			userclock = atoi(optarg);
			maxclocks = userclock + 1;
			break;
		default:
			printf("Usage: %s [-t <secs>] [-c <clockid>]\n", argv[0]);
			printf("	-t: Number of seconds to run\n");
			printf("	-c: clockid to use (default, all clockids)\n");
			exit(-1);
		}
	}

	setbuf(stdout, NULL);

	for (clockid = userclock; clockid < maxclocks; clockid++) {

		if (clockid == CLOCK_HWSPECIFIC)
			continue;

		if (!clock_gettime(clockid, &ts)) {
			printf("Consistent %-30s ", clockstring(clockid));
			if (consistency_test(clockid, runtime))
				return ksft_exit_fail();
		}
	}
	return ksft_exit_pass();
}