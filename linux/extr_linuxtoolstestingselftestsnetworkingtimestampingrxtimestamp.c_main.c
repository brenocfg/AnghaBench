#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int enabled; char* friendly_name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 char getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  long_options ; 
 void* op_size ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  print_test_case (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ run_test_case (TYPE_1__,TYPE_1__) ; 
 TYPE_1__* socket_types ; 
 TYPE_1__* test_cases ; 

int main(int argc, char **argv)
{
	bool all_protocols = true;
	bool all_tests = true;
	int arg_index = 0;
	int failures = 0;
	int s, t;
	char opt;

	while ((opt = getopt_long(argc, argv, "", long_options,
				  &arg_index)) != -1) {
		switch (opt) {
		case 'l':
			for (t = 0; t < ARRAY_SIZE(test_cases); t++) {
				printf("%d\t", t);
				print_test_case(&test_cases[t]);
			}
			return 0;
		case 'n':
			t = atoi(optarg);
			if (t >= ARRAY_SIZE(test_cases))
				error(1, 0, "Invalid test case: %d", t);
			all_tests = false;
			test_cases[t].enabled = true;
			break;
		case 's':
			op_size = atoi(optarg);
			break;
		case 't':
			all_protocols = false;
			socket_types[2].enabled = true;
			break;
		case 'u':
			all_protocols = false;
			socket_types[1].enabled = true;
			break;
		case 'i':
			all_protocols = false;
			socket_types[0].enabled = true;
			break;
		default:
			error(1, 0, "Failed to parse parameters.");
		}
	}

	for (s = 0; s < ARRAY_SIZE(socket_types); s++) {
		if (!all_protocols && !socket_types[s].enabled)
			continue;

		printf("Testing %s...\n", socket_types[s].friendly_name);
		for (t = 0; t < ARRAY_SIZE(test_cases); t++) {
			if (!all_tests && !test_cases[t].enabled)
				continue;

			printf("Starting testcase %d...\n", t);
			if (run_test_case(socket_types[s], test_cases[t])) {
				failures++;
				printf("FAILURE in test case ");
				print_test_case(&test_cases[t]);
			}
		}
	}
	if (!failures)
		printf("PASSED.\n");
	return failures;
}