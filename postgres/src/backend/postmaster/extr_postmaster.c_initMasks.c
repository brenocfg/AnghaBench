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
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int* ListenSocket ; 
 int MAXLISTEN ; 
 int PGINVALID_SOCKET ; 

__attribute__((used)) static int
initMasks(fd_set *rmask)
{
	int			maxsock = -1;
	int			i;

	FD_ZERO(rmask);

	for (i = 0; i < MAXLISTEN; i++)
	{
		int			fd = ListenSocket[i];

		if (fd == PGINVALID_SOCKET)
			break;
		FD_SET(fd, rmask);

		if (fd > maxsock)
			maxsock = fd;
	}

	return maxsock + 1;
}