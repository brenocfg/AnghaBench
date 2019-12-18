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
struct socket {int dummy; } ;
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ kernel_getsockname (struct socket*,struct sockaddr*) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned short xs_sock_getport(struct socket *sock)
{
	struct sockaddr_storage buf;
	unsigned short port = 0;

	if (kernel_getsockname(sock, (struct sockaddr *)&buf) < 0)
		goto out;
	switch (buf.ss_family) {
	case AF_INET6:
		port = ntohs(((struct sockaddr_in6 *)&buf)->sin6_port);
		break;
	case AF_INET:
		port = ntohs(((struct sockaddr_in *)&buf)->sin_port);
	}
out:
	return port;
}