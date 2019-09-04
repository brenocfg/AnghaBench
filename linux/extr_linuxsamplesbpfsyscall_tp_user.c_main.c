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
struct rlimit {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int test (char*,int) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv)
{
	struct rlimit r = {RLIM_INFINITY, RLIM_INFINITY};
	int opt, num_progs = 1;
	char filename[256];

	while ((opt = getopt(argc, argv, "i:h")) != -1) {
		switch (opt) {
		case 'i':
			num_progs = atoi(optarg);
			break;
		case 'h':
		default:
			usage(argv[0]);
			return 0;
		}
	}

	setrlimit(RLIMIT_MEMLOCK, &r);
	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

	return test(filename, num_progs);
}