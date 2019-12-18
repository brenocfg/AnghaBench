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
 int /*<<< orphan*/  EINTR ; 
 scalar_t__ UNBLOCKED_SIGNAL_QUEUE () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pgwin32_dispatch_queued_signals () ; 

__attribute__((used)) static int
pgwin32_poll_signals(void)
{
	if (UNBLOCKED_SIGNAL_QUEUE())
	{
		pgwin32_dispatch_queued_signals();
		errno = EINTR;
		return 1;
	}
	return 0;
}