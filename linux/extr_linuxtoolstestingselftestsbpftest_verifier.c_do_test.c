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
struct bpf_test {char* descr; int /*<<< orphan*/  prog_type; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  do_test_single (struct bpf_test*,int,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  set_admin (int) ; 
 int skips ; 
 struct bpf_test* tests ; 
 scalar_t__ unpriv_disabled ; 

__attribute__((used)) static int do_test(bool unpriv, unsigned int from, unsigned int to)
{
	int i, passes = 0, errors = 0;

	for (i = from; i < to; i++) {
		struct bpf_test *test = &tests[i];

		/* Program types that are not supported by non-root we
		 * skip right away.
		 */
		if (!test->prog_type && unpriv_disabled) {
			printf("#%d/u %s SKIP\n", i, test->descr);
			skips++;
		} else if (!test->prog_type) {
			if (!unpriv)
				set_admin(false);
			printf("#%d/u %s ", i, test->descr);
			do_test_single(test, true, &passes, &errors);
			if (!unpriv)
				set_admin(true);
		}

		if (unpriv) {
			printf("#%d/p %s SKIP\n", i, test->descr);
			skips++;
		} else {
			printf("#%d/p %s ", i, test->descr);
			do_test_single(test, false, &passes, &errors);
		}
	}

	printf("Summary: %d PASSED, %d SKIPPED, %d FAILED\n", passes,
	       skips, errors);
	return errors ? EXIT_FAILURE : EXIT_SUCCESS;
}