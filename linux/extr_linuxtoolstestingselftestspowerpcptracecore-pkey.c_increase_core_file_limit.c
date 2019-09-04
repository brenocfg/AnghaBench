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
struct rlimit {scalar_t__ rlim_cur; scalar_t__ rlim_max; } ;

/* Variables and functions */
 scalar_t__ CORE_FILE_LIMIT ; 
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  RLIMIT_FSIZE ; 
 scalar_t__ RLIM_INFINITY ; 
 int TEST_PASS ; 
 int getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

__attribute__((used)) static int increase_core_file_limit(void)
{
	struct rlimit rlim;
	int ret;

	ret = getrlimit(RLIMIT_CORE, &rlim);
	FAIL_IF(ret);

	if (rlim.rlim_cur != RLIM_INFINITY && rlim.rlim_cur < CORE_FILE_LIMIT) {
		rlim.rlim_cur = CORE_FILE_LIMIT;

		if (rlim.rlim_max != RLIM_INFINITY &&
		    rlim.rlim_max < CORE_FILE_LIMIT)
			rlim.rlim_max = CORE_FILE_LIMIT;

		ret = setrlimit(RLIMIT_CORE, &rlim);
		FAIL_IF(ret);
	}

	ret = getrlimit(RLIMIT_FSIZE, &rlim);
	FAIL_IF(ret);

	if (rlim.rlim_cur != RLIM_INFINITY && rlim.rlim_cur < CORE_FILE_LIMIT) {
		rlim.rlim_cur = CORE_FILE_LIMIT;

		if (rlim.rlim_max != RLIM_INFINITY &&
		    rlim.rlim_max < CORE_FILE_LIMIT)
			rlim.rlim_max = CORE_FILE_LIMIT;

		ret = setrlimit(RLIMIT_FSIZE, &rlim);
		FAIL_IF(ret);
	}

	return TEST_PASS;
}