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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int PF_RDS ; 
 int /*<<< orphan*/  POLLERR ; 
 int /*<<< orphan*/  POLLIN ; 
 scalar_t__ cfg_waittime_ms ; 
 scalar_t__ completions ; 
 scalar_t__ do_poll (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_recv_completions (int,int) ; 
 scalar_t__ expected_completions ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ gettimeofday_ms () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void do_recv_remaining_completions(int fd, int domain)
{
	int64_t tstop = gettimeofday_ms() + cfg_waittime_ms;

	while (completions < expected_completions &&
	       gettimeofday_ms() < tstop) {
		if (do_poll(fd, domain == PF_RDS ? POLLIN : POLLERR))
			do_recv_completions(fd, domain);
	}

	if (completions < expected_completions)
		fprintf(stderr, "missing notifications: %lu < %lu\n",
			completions, expected_completions);
}