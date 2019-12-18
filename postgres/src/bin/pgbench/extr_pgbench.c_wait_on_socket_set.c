#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_3__ {int /*<<< orphan*/  fds; scalar_t__ maxfd; } ;
typedef  TYPE_1__ socket_set ;
typedef  int int64 ;

/* Variables and functions */
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
wait_on_socket_set(socket_set *sa, int64 usecs)
{
	if (usecs > 0)
	{
		struct timeval timeout;

		timeout.tv_sec = usecs / 1000000;
		timeout.tv_usec = usecs % 1000000;
		return select(sa->maxfd + 1, &sa->fds, NULL, NULL, &timeout);
	}
	else
	{
		return select(sa->maxfd + 1, &sa->fds, NULL, NULL, NULL);
	}
}