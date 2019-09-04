#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin6_family; } ;
struct TYPE_4__ {int xp_addrlen; TYPE_2__ xp_raddr; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct sockaddr_storage const*,int) ; 

void
__xprt_set_raddr(SVCXPRT *xprt, const struct sockaddr_storage *ss)
{
	switch (ss->ss_family) {
	case AF_INET6:
		memcpy(&xprt->xp_raddr, ss, sizeof(struct sockaddr_in6));
		xprt->xp_addrlen = sizeof (struct sockaddr_in6);
		break;
	case AF_INET:
		memcpy(&xprt->xp_raddr, ss, sizeof(struct sockaddr_in));
		xprt->xp_addrlen = sizeof (struct sockaddr_in);
		break;
	default:
		xprt->xp_raddr.sin6_family = AF_UNSPEC;
		xprt->xp_addrlen = sizeof (struct sockaddr);
		break;
	}
}