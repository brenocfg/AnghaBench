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
struct rlimit {int rlim_cur; int rlim_max; } ;
typedef  int rlim_t ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

__attribute__((used)) static rlim_t max_openfds(void)
{
	struct rlimit rl;
	rlim_t limit = getrlimit(RLIMIT_NOFILE, &rl);

	if (limit != 0)
		return 32;

	limit = rl.rlim_cur;
	rl.rlim_cur = rl.rlim_max;

	/* Return ~75% of max possible */
	if (setrlimit(RLIMIT_NOFILE, &rl) == 0) {
		limit = rl.rlim_max - (rl.rlim_max >> 2);
		/*
		 * 20K is arbitrary. If the limit is set to max possible
		 * value, the memory usage increases to more than double.
		 */
		return limit > 20480 ?  20480 : limit;
	}

	return limit;
}