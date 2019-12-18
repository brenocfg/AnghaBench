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

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

void rlimit__bump_memlock(void)
{
	struct rlimit rlim;

	if (getrlimit(RLIMIT_MEMLOCK, &rlim) == 0) {
		rlim.rlim_cur *= 4;
		rlim.rlim_max *= 4;

		if (setrlimit(RLIMIT_MEMLOCK, &rlim) < 0) {
			rlim.rlim_cur /= 2;
			rlim.rlim_max /= 2;

			if (setrlimit(RLIMIT_MEMLOCK, &rlim) < 0)
				pr_debug("Couldn't bump rlimit(MEMLOCK), failures may take place when creating BPF maps, etc\n");
		}
	}
}