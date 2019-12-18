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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct fib_nh {scalar_t__ fib_nh_gw_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int fib_check_nh_nongw (struct net*,struct fib_nh*,struct netlink_ext_ack*) ; 
 int fib_check_nh_v4_gw (struct net*,struct fib_nh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int fib_check_nh_v6_gw (struct net*,struct fib_nh*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

int fib_check_nh(struct net *net, struct fib_nh *nh, u32 table, u8 scope,
		 struct netlink_ext_ack *extack)
{
	int err;

	if (nh->fib_nh_gw_family == AF_INET)
		err = fib_check_nh_v4_gw(net, nh, table, scope, extack);
	else if (nh->fib_nh_gw_family == AF_INET6)
		err = fib_check_nh_v6_gw(net, nh, table, extack);
	else
		err = fib_check_nh_nongw(net, nh, extack);

	return err;
}