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
struct rlimit {int rlim_cur; } ;
typedef  int rlim_t ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int RLIM_INFINITY ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static rlim_t get_fd_limit(void)
{
	struct rlimit l;
	rlim_t limit = 0;

	/* Allow half of the current open fd limit. */
	if (getrlimit(RLIMIT_NOFILE, &l) == 0) {
		if (l.rlim_cur == RLIM_INFINITY)
			limit = l.rlim_cur;
		else
			limit = l.rlim_cur / 2;
	} else {
		pr_err("failed to get fd limit\n");
		limit = 1;
	}

	return limit;
}