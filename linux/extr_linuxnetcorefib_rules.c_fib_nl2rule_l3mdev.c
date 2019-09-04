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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct fib_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 

__attribute__((used)) static int fib_nl2rule_l3mdev(struct nlattr *nla, struct fib_rule *nlrule,
			      struct netlink_ext_ack *extack)
{
	NL_SET_ERR_MSG(extack, "l3mdev support is not enabled in kernel");
	return -1;
}