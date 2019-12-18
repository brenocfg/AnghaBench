#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/  (* PgIfAddrCallback ) (struct sockaddr*,struct sockaddr*,void*) ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  pg_sockaddr_cidr_mask (struct sockaddr_storage*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct sockaddr*,struct sockaddr*,void*) ; 

__attribute__((used)) static void
run_ifaddr_callback(PgIfAddrCallback callback, void *cb_data,
					struct sockaddr *addr, struct sockaddr *mask)
{
	struct sockaddr_storage fullmask;

	if (!addr)
		return;

	/* Check that the mask is valid */
	if (mask)
	{
		if (mask->sa_family != addr->sa_family)
		{
			mask = NULL;
		}
		else if (mask->sa_family == AF_INET)
		{
			if (((struct sockaddr_in *) mask)->sin_addr.s_addr == INADDR_ANY)
				mask = NULL;
		}
#ifdef HAVE_IPV6
		else if (mask->sa_family == AF_INET6)
		{
			if (IN6_IS_ADDR_UNSPECIFIED(&((struct sockaddr_in6 *) mask)->sin6_addr))
				mask = NULL;
		}
#endif
	}

	/* If mask is invalid, generate our own fully-set mask */
	if (!mask)
	{
		pg_sockaddr_cidr_mask(&fullmask, NULL, addr->sa_family);
		mask = (struct sockaddr *) &fullmask;
	}

	(*callback) (addr, mask, cb_data);
}