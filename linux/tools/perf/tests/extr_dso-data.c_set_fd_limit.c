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

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  pr_debug (char*,long,int) ; 
 int setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

__attribute__((used)) static int set_fd_limit(int n)
{
	struct rlimit rlim;

	if (getrlimit(RLIMIT_NOFILE, &rlim))
		return -1;

	pr_debug("file limit %ld, new %d\n", (long) rlim.rlim_cur, n);

	rlim.rlim_cur = n;
	return setrlimit(RLIMIT_NOFILE, &rlim);
}