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
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int SOCKET_ERROR ; 
 scalar_t__ WSAEINTR ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ errno ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
select_loop(int maxFd, fd_set *workerset)
{
	int			i;
	fd_set		saveSet = *workerset;

	for (;;)
	{
		*workerset = saveSet;
		i = select(maxFd + 1, workerset, NULL, NULL, NULL);

#ifndef WIN32
		if (i < 0 && errno == EINTR)
			continue;
#else
		if (i == SOCKET_ERROR && WSAGetLastError() == WSAEINTR)
			continue;
#endif
		break;
	}

	return i;
}