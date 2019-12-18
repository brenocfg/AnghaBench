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
struct TYPE_3__ {int len; char* buf; } ;
typedef  TYPE_1__ WSABUF ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EWOULDBLOCK ; 
 int FD_CLOSE ; 
 int FD_WRITE ; 
 int /*<<< orphan*/  INFINITE ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  TranslateSocketError () ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 int WSASend (int /*<<< orphan*/ ,TYPE_1__*,int,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ pgwin32_noblock ; 
 scalar_t__ pgwin32_poll_signals () ; 
 scalar_t__ pgwin32_waitforsinglesocket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
pgwin32_send(SOCKET s, const void *buf, int len, int flags)
{
	WSABUF		wbuf;
	int			r;
	DWORD		b;

	if (pgwin32_poll_signals())
		return -1;

	wbuf.len = len;
	wbuf.buf = (char *) buf;

	/*
	 * Readiness of socket to send data to UDP socket may be not true: socket
	 * can become busy again! So loop until send or error occurs.
	 */
	for (;;)
	{
		r = WSASend(s, &wbuf, 1, &b, flags, NULL, NULL);
		if (r != SOCKET_ERROR && b > 0)
			/* Write succeeded right away */
			return b;

		if (r == SOCKET_ERROR &&
			WSAGetLastError() != WSAEWOULDBLOCK)
		{
			TranslateSocketError();
			return -1;
		}

		if (pgwin32_noblock)
		{
			/*
			 * No data sent, and we are in "emulated non-blocking mode", so
			 * return indicating that we'd block if we were to continue.
			 */
			errno = EWOULDBLOCK;
			return -1;
		}

		/* No error, zero bytes (win2000+) or error+WSAEWOULDBLOCK (<=nt4) */

		if (pgwin32_waitforsinglesocket(s, FD_WRITE | FD_CLOSE, INFINITE) == 0)
			return -1;
	}

	return -1;
}