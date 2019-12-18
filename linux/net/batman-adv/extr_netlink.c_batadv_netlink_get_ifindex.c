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
typedef  int /*<<< orphan*/  u32 ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENL_HDRLEN ; 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct nlattr* nlmsg_find_attr (struct nlmsghdr const*,int /*<<< orphan*/ ,int) ; 

int
batadv_netlink_get_ifindex(const struct nlmsghdr *nlh, int attrtype)
{
	struct nlattr *attr = nlmsg_find_attr(nlh, GENL_HDRLEN, attrtype);

	return (attr && nla_len(attr) == sizeof(u32)) ? nla_get_u32(attr) : 0;
}