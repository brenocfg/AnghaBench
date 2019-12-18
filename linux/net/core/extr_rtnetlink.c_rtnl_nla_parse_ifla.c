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

/* Variables and functions */
 int /*<<< orphan*/  IFLA_MAX ; 
 int /*<<< orphan*/  ifla_policy ; 
 int nla_parse_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

int rtnl_nla_parse_ifla(struct nlattr **tb, const struct nlattr *head, int len,
			struct netlink_ext_ack *exterr)
{
	return nla_parse_deprecated(tb, IFLA_MAX, head, len, ifla_policy,
				    exterr);
}