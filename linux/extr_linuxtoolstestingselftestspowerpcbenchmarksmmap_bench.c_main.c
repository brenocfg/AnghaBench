#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 char getopt_long (int,char**,char*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  iterations ; 
 int /*<<< orphan*/  optarg ; 
 TYPE_1__* options ; 
 int test_harness (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_harness_set_timeout (int) ; 
 int /*<<< orphan*/  test_mmap ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
	signed char c;
	while (1) {
		int option_index = 0;

		c = getopt_long(argc, argv, "", options, &option_index);

		if (c == -1)
			break;

		switch (c) {
		case 0:
			if (options[option_index].flag != 0)
				break;

			usage();
			exit(1);
			break;
		case 'i':
			iterations = atoi(optarg);
			break;
		default:
			usage();
			exit(1);
		}
	}

	test_harness_set_timeout(300);
	return test_harness(test_mmap, "mmap_bench");
}