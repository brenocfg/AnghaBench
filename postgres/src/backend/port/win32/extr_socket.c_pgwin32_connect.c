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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CONNECT ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  TranslateSocketError () ; 
 int WSAConnect (int /*<<< orphan*/ ,struct sockaddr const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ pgwin32_waitforsinglesocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pgwin32_connect(SOCKET s, const struct sockaddr *addr, int addrlen)
{
	int			r;

	r = WSAConnect(s, addr, addrlen, NULL, NULL, NULL, NULL);
	if (r == 0)
		return 0;

	if (WSAGetLastError() != WSAEWOULDBLOCK)
	{
		TranslateSocketError();
		return -1;
	}

	while (pgwin32_waitforsinglesocket(s, FD_CONNECT, INFINITE) == 0)
	{
		/* Loop endlessly as long as we are just delivering signals */
	}

	return 0;
}