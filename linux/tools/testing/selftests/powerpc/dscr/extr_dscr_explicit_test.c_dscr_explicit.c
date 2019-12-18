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
 unsigned long COUNT ; 
 unsigned long DSCR_MAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 unsigned long get_dscr () ; 
 unsigned long get_dscr_usr () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  set_dscr (unsigned long) ; 
 int /*<<< orphan*/  set_dscr_usr (unsigned long) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 double uniform_deviate (int /*<<< orphan*/ ) ; 

int dscr_explicit(void)
{
	unsigned long i, dscr = 0;

	srand(getpid());
	set_dscr(dscr);

	for (i = 0; i < COUNT; i++) {
		unsigned long cur_dscr, cur_dscr_usr;
		double ret = uniform_deviate(rand());

		if (ret < 0.001) {
			dscr++;
			if (dscr > DSCR_MAX)
				dscr = 0;

			set_dscr(dscr);
		}

		cur_dscr = get_dscr();
		if (cur_dscr != dscr) {
			fprintf(stderr, "Kernel DSCR should be %ld but "
					"is %ld\n", dscr, cur_dscr);
			return 1;
		}

		ret = uniform_deviate(rand());
		if (ret < 0.001) {
			dscr++;
			if (dscr > DSCR_MAX)
				dscr = 0;

			set_dscr_usr(dscr);
		}

		cur_dscr_usr = get_dscr_usr();
		if (cur_dscr_usr != dscr) {
			fprintf(stderr, "User DSCR should be %ld but "
					"is %ld\n", dscr, cur_dscr_usr);
			return 1;
		}
	}
	return 0;
}