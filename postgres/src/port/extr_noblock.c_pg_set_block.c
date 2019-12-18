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
typedef  int /*<<< orphan*/  pgsocket ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ioctlsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

bool
pg_set_block(pgsocket sock)
{
#if !defined(WIN32)
	int			flags;

	flags = fcntl(sock, F_GETFL);
	if (flags < 0)
		return false;
	if (fcntl(sock, F_SETFL, (flags & ~O_NONBLOCK)) == -1)
		return false;
	return true;
#else
	unsigned long ioctlsocket_ret = 0;

	/* Returns non-0 on failure, while fcntl() returns -1 on failure */
	return (ioctlsocket(sock, FIONBIO, &ioctlsocket_ret) == 0);
#endif
}