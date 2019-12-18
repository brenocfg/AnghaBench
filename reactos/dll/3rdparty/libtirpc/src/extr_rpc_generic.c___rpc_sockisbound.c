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
struct sockaddr_un {int /*<<< orphan*/ * sun_path; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin_port; } ;
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/ * sun_path; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin_port; } ;
struct sockaddr_in {int /*<<< orphan*/ * sun_path; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_LOCAL 128 
 scalar_t__ SOCKET_ERROR ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_un*,struct sockaddr_storage*,int) ; 

int
__rpc_sockisbound(SOCKET fd)
{
	struct sockaddr_storage ss;
	union {
		struct sockaddr_in  sin;
		struct sockaddr_in6 sin6;
#ifdef AF_LOCAL
		struct sockaddr_un  usin;
#endif
	} u_addr;
	socklen_t slen;

	slen = sizeof (struct sockaddr_storage);
	if (getsockname(fd, (struct sockaddr *)(void *)&ss, &slen) == SOCKET_ERROR)
		return 0;

	switch (ss.ss_family) {
		case AF_INET:
			memcpy(&u_addr.sin, &ss, sizeof(u_addr.sin)); 
			return (u_addr.sin.sin_port != 0);
#ifdef INET6
		case AF_INET6:
			memcpy(&u_addr.sin6, &ss, sizeof(u_addr.sin6)); 
			return (u_addr.sin6.sin6_port != 0);
#endif
#ifdef AF_LOCAL
		case AF_LOCAL:
			/* XXX check this */
			memcpy(&u_addr.usin, &ss, sizeof(u_addr.usin)); 
			return (u_addr.usin.sun_path[0] != 0);
#endif
		default:
			break;
	}

	return 0;
}