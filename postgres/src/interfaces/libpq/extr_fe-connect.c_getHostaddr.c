#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct TYPE_7__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct TYPE_8__ {struct sockaddr_storage addr; } ;
struct TYPE_9__ {TYPE_3__ raddr; } ;
typedef  TYPE_4__ PGconn ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/ * pg_inet_net_ntop (scalar_t__,int /*<<< orphan*/ *,int,char*,int) ; 

__attribute__((used)) static void
getHostaddr(PGconn *conn, char *host_addr, int host_addr_len)
{
	struct sockaddr_storage *addr = &conn->raddr.addr;

	if (addr->ss_family == AF_INET)
	{
		if (pg_inet_net_ntop(AF_INET,
							 &((struct sockaddr_in *) addr)->sin_addr.s_addr,
							 32,
							 host_addr, host_addr_len) == NULL)
			host_addr[0] = '\0';
	}
#ifdef HAVE_IPV6
	else if (addr->ss_family == AF_INET6)
	{
		if (pg_inet_net_ntop(AF_INET6,
							 &((struct sockaddr_in6 *) addr)->sin6_addr.s6_addr,
							 128,
							 host_addr, host_addr_len) == NULL)
			host_addr[0] = '\0';
	}
#endif
	else
		host_addr[0] = '\0';
}