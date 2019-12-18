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
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  TranslateSocketError () ; 
 scalar_t__ WSASocket (int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSA_FLAG_OVERLAPPED ; 
 scalar_t__ errno ; 
 scalar_t__ ioctlsocket (scalar_t__,int /*<<< orphan*/ ,unsigned long*) ; 

SOCKET
pgwin32_socket(int af, int type, int protocol)
{
	SOCKET		s;
	unsigned long on = 1;

	s = WSASocket(af, type, protocol, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (s == INVALID_SOCKET)
	{
		TranslateSocketError();
		return INVALID_SOCKET;
	}

	if (ioctlsocket(s, FIONBIO, &on))
	{
		TranslateSocketError();
		return INVALID_SOCKET;
	}
	errno = 0;

	return s;
}