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
struct netlink_ext_ack {int dummy; } ;
struct fib6_info {int dummy; } ;
struct fib6_config {int /*<<< orphan*/  fc_nlinfo; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fib6_info*) ; 
 int PTR_ERR (struct fib6_info*) ; 
 int __ip6_ins_rt (struct fib6_info*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 struct fib6_info* ip6_route_info_create (struct fib6_config*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

int ip6_route_add(struct fib6_config *cfg, gfp_t gfp_flags,
		  struct netlink_ext_ack *extack)
{
	struct fib6_info *rt;
	int err;

	rt = ip6_route_info_create(cfg, gfp_flags, extack);
	if (IS_ERR(rt))
		return PTR_ERR(rt);

	err = __ip6_ins_rt(rt, &cfg->fc_nlinfo, extack);
	fib6_info_release(rt);

	return err;
}