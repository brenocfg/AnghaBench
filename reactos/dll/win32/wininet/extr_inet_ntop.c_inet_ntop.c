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
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  WSAEAFNOSUPPORT ; 
 int /*<<< orphan*/  WSASetLastError (int /*<<< orphan*/ ) ; 
 char const* inet_ntop4 (void const*,char*,int /*<<< orphan*/ ) ; 
 char const* inet_ntop6 (void const*,char*,int /*<<< orphan*/ ) ; 

const char *
inet_ntop(int af, const void *src, char *dst, socklen_t size)
{

	switch (af) {
	case AF_INET:
		return (inet_ntop4(src, dst, size));
#ifdef INET6
	case AF_INET6:
		return (inet_ntop6(src, dst, size));
#endif
	default:
		WSASetLastError(WSAEAFNOSUPPORT);
		return (NULL);
	}
	/* NOTREACHED */
}