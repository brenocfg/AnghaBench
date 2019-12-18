#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  maxattr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GENL_HDRLEN ; 
 struct nlattr** genl_family_attrbuf (TYPE_1__*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr const*,int /*<<< orphan*/ ,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ tipc_genl_family ; 
 int /*<<< orphan*/  tipc_nl_policy ; 

int tipc_nlmsg_parse(const struct nlmsghdr *nlh, struct nlattr ***attr)
{
	u32 maxattr = tipc_genl_family.maxattr;

	*attr = genl_family_attrbuf(&tipc_genl_family);
	if (!*attr)
		return -EOPNOTSUPP;

	return nlmsg_parse_deprecated(nlh, GENL_HDRLEN, *attr, maxattr,
				      tipc_nl_policy, NULL);
}