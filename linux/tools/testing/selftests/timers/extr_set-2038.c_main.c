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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 scalar_t__ YEAR_1901 ; 
 scalar_t__ YEAR_1970 ; 
 scalar_t__ YEAR_2038 ; 
 scalar_t__ YEAR_2262 ; 
 scalar_t__ YEAR_MAX ; 
 int do_tests () ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ is32bits () ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  settime (scalar_t__) ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	int ret = 0;
	int opt, dangerous = 0;
	time_t start;

	/* Process arguments */
	while ((opt = getopt(argc, argv, "d")) != -1) {
		switch (opt) {
		case 'd':
			dangerous = 1;
		}
	}

	start = time(0);

	/* First test that crazy values don't work */
	if (!settime(YEAR_1901)) {
		ret = -1;
		goto out;
	}
	if (!settime(YEAR_MAX)) {
		ret = -1;
		goto out;
	}
	if (!is32bits() && !settime(YEAR_2262)) {
		ret = -1;
		goto out;
	}

	/* Now test behavior near edges */
	settime(YEAR_1970);
	ret = do_tests();
	if (ret)
		goto out;

	settime(YEAR_2038 - 600);
	ret = do_tests();
	if (ret)
		goto out;

	/* The rest of the tests can blowup on 32bit systems */
	if (is32bits() && !dangerous)
		goto out;
	/* Test rollover behavior 32bit edge */
	settime(YEAR_2038 - 10);
	ret = do_tests();
	if (ret)
		goto out;

	settime(YEAR_2262 - 600);
	ret = do_tests();

out:
	/* restore clock */
	settime(start);
	if (ret)
		return ksft_exit_fail();
	return ksft_exit_pass();
}