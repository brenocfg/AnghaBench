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
struct net_device {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  IFLA_INET6_MAX ; 
 int /*<<< orphan*/  __in6_dev_get (struct net_device const*) ; 
 int /*<<< orphan*/  inet6_af_policy ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inet6_validate_link_af(const struct net_device *dev,
				  const struct nlattr *nla)
{
	struct nlattr *tb[IFLA_INET6_MAX + 1];

	if (dev && !__in6_dev_get(dev))
		return -EAFNOSUPPORT;

	return nla_parse_nested(tb, IFLA_INET6_MAX, nla, inet6_af_policy,
				NULL);
}