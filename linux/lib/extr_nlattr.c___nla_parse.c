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
struct nla_policy {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int __nla_validate_parse (struct nlattr const*,int,int,struct nla_policy const*,unsigned int,struct netlink_ext_ack*,struct nlattr**) ; 

int __nla_parse(struct nlattr **tb, int maxtype,
		const struct nlattr *head, int len,
		const struct nla_policy *policy, unsigned int validate,
		struct netlink_ext_ack *extack)
{
	return __nla_validate_parse(head, len, maxtype, policy, validate,
				    extack, tb);
}