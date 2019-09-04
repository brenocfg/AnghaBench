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
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EXIT_FAILURE ; 
 char* UNPRIV_SYSCTL ; 
 unsigned int atoi (char*) ; 
 int /*<<< orphan*/  bpf_semi_rand_init () ; 
 int do_test (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  get_unpriv_disabled () ; 
 int /*<<< orphan*/  is_admin () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  tests ; 
 scalar_t__ unpriv_disabled ; 

int main(int argc, char **argv)
{
	unsigned int from = 0, to = ARRAY_SIZE(tests);
	bool unpriv = !is_admin();

	if (argc == 3) {
		unsigned int l = atoi(argv[argc - 2]);
		unsigned int u = atoi(argv[argc - 1]);

		if (l < to && u < to) {
			from = l;
			to   = u + 1;
		}
	} else if (argc == 2) {
		unsigned int t = atoi(argv[argc - 1]);

		if (t < to) {
			from = t;
			to   = t + 1;
		}
	}

	get_unpriv_disabled();
	if (unpriv && unpriv_disabled) {
		printf("Cannot run as unprivileged user with sysctl %s.\n",
		       UNPRIV_SYSCTL);
		return EXIT_FAILURE;
	}

	bpf_semi_rand_init();
	return do_test(unpriv, from, to);
}