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
 int EBADF ; 
 int EINVAL ; 
 size_t IFLA_PPP_DEV_FD ; 
 scalar_t__ nla_get_s32 (struct nlattr*) ; 

__attribute__((used)) static int ppp_nl_validate(struct nlattr *tb[], struct nlattr *data[],
			   struct netlink_ext_ack *extack)
{
	if (!data)
		return -EINVAL;

	if (!data[IFLA_PPP_DEV_FD])
		return -EINVAL;
	if (nla_get_s32(data[IFLA_PPP_DEV_FD]) < 0)
		return -EBADF;

	return 0;
}