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
struct broadif {int dummy; } ;

/* Variables and functions */
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int
/*ARGSUSED*/
__rpc_broadenable(int af, int s, struct broadif *bip)
{
	int o = 1;

#if 0
	if (af == AF_INET6) {
		fprintf(stderr, "set v6 multicast if to %d\n", bip->index);
		if (setsockopt(s, IPPROTO_IPV6, IPV6_MULTICAST_IF, &bip->index,
		    sizeof bip->index) < 0)
			return -1;
	} else
#endif
		if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &o, sizeof o) == SOCKET_ERROR)
			return -1;

	return 0;
}