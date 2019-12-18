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
struct rtnexthop {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct fib_info {int dummy; } ;
struct fib_config {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 

__attribute__((used)) static int fib_get_nhs(struct fib_info *fi, struct rtnexthop *rtnh,
		       int remaining, struct fib_config *cfg,
		       struct netlink_ext_ack *extack)
{
	NL_SET_ERR_MSG(extack, "Multipath support not enabled in kernel");

	return -EINVAL;
}