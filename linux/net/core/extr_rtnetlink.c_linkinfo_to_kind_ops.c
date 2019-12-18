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
struct rtnl_link_ops {int dummy; } ;
struct nlattr {int dummy; } ;
typedef  int /*<<< orphan*/  kind ;

/* Variables and functions */
 size_t IFLA_INFO_KIND ; 
 int /*<<< orphan*/  IFLA_INFO_MAX ; 
 int MODULE_NAME_LEN ; 
 int /*<<< orphan*/  ifla_info_policy ; 
 scalar_t__ nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_strlcpy (char*,struct nlattr*,int) ; 
 struct rtnl_link_ops* rtnl_link_ops_get (char*) ; 

__attribute__((used)) static const struct rtnl_link_ops *linkinfo_to_kind_ops(const struct nlattr *nla)
{
	const struct rtnl_link_ops *ops = NULL;
	struct nlattr *linfo[IFLA_INFO_MAX + 1];

	if (nla_parse_nested_deprecated(linfo, IFLA_INFO_MAX, nla, ifla_info_policy, NULL) < 0)
		return NULL;

	if (linfo[IFLA_INFO_KIND]) {
		char kind[MODULE_NAME_LEN];

		nla_strlcpy(kind, linfo[IFLA_INFO_KIND], sizeof(kind));
		ops = rtnl_link_ops_get(kind);
	}

	return ops;
}