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

/* Variables and functions */
 int AF_INET ; 
 int ENOENT ; 
 int IPPROTO_RAW ; 
 int /*<<< orphan*/  NETLINK_SOCK_DIAG ; 
 int /*<<< orphan*/  PF_NETLINK ; 
 int /*<<< orphan*/ * inet_protos ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int request_module (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  sock_is_registered (int) ; 

int sock_load_diag_module(int family, int protocol)
{
	if (!protocol) {
		if (!sock_is_registered(family))
			return -ENOENT;

		return request_module("net-pf-%d-proto-%d-type-%d", PF_NETLINK,
				      NETLINK_SOCK_DIAG, family);
	}

#ifdef CONFIG_INET
	if (family == AF_INET &&
	    protocol != IPPROTO_RAW &&
	    !rcu_access_pointer(inet_protos[protocol]))
		return -ENOENT;
#endif

	return request_module("net-pf-%d-proto-%d-type-%d-%d", PF_NETLINK,
			      NETLINK_SOCK_DIAG, family, protocol);
}