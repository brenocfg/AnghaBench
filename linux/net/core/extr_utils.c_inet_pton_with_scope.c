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
typedef  scalar_t__ u16 ;
struct sockaddr_storage {int dummy; } ;
struct net {int dummy; } ;
typedef  int __kernel_sa_family_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNSPEC 128 
 int EINVAL ; 
 int inet4_pton (char const*,scalar_t__,struct sockaddr_storage*) ; 
 int inet6_pton (struct net*,char const*,scalar_t__,struct sockaddr_storage*) ; 
 scalar_t__ kstrtou16 (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int inet_pton_with_scope(struct net *net, __kernel_sa_family_t af,
		const char *src, const char *port, struct sockaddr_storage *addr)
{
	u16 port_num;
	int ret = -EINVAL;

	if (port) {
		if (kstrtou16(port, 0, &port_num))
			return -EINVAL;
	} else {
		port_num = 0;
	}

	switch (af) {
	case AF_INET:
		ret = inet4_pton(src, port_num, addr);
		break;
	case AF_INET6:
		ret = inet6_pton(net, src, port_num, addr);
		break;
	case AF_UNSPEC:
		ret = inet4_pton(src, port_num, addr);
		if (ret)
			ret = inet6_pton(net, src, port_num, addr);
		break;
	default:
		pr_err("unexpected address family %d\n", af);
	}

	return ret;
}