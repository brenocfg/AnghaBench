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
struct timeval {int member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ CancelRequested ; 
 scalar_t__ EINTR ; 
 int SOCKET_ERROR ; 
 scalar_t__ WSAEINTR ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ errno ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
select_loop(int maxFd, fd_set *workerset, bool *aborting)
{
	int			i;
	fd_set		saveSet = *workerset;

	if (CancelRequested)
	{
		*aborting = true;
		return -1;
	}
	else
		*aborting = false;

	for (;;)
	{
		/*
		 * On Windows, we need to check once in a while for cancel requests;
		 * on other platforms we rely on select() returning when interrupted.
		 */
		struct timeval *tvp;
#ifdef WIN32
		struct timeval tv = {0, 1000000};

		tvp = &tv;
#else
		tvp = NULL;
#endif

		*workerset = saveSet;
		i = select(maxFd + 1, workerset, NULL, NULL, tvp);

#ifdef WIN32
		if (i == SOCKET_ERROR)
		{
			i = -1;

			if (WSAGetLastError() == WSAEINTR)
				errno = EINTR;
		}
#endif

		if (i < 0 && errno == EINTR)
			continue;			/* ignore this */
		if (i < 0 || CancelRequested)
			*aborting = true;	/* but not this */
		if (i == 0)
			continue;			/* timeout (Win32 only) */
		break;
	}

	return i;
}