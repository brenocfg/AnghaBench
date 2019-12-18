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
struct test {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 scalar_t__ strcasestr (int /*<<< orphan*/ ,char const*) ; 
 long strtoul (char const*,char**,int) ; 

__attribute__((used)) static bool perf_test__matches(struct test *test, int curr, int argc, const char *argv[])
{
	int i;

	if (argc == 0)
		return true;

	for (i = 0; i < argc; ++i) {
		char *end;
		long nr = strtoul(argv[i], &end, 10);

		if (*end == '\0') {
			if (nr == curr + 1)
				return true;
			continue;
		}

		if (strcasestr(test->desc, argv[i]))
			return true;
	}

	return false;
}