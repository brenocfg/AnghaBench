#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct netlink_callback {scalar_t__* args; } ;
struct ip_set_net {int dummy; } ;
struct ip_set {int /*<<< orphan*/  name; TYPE_1__* variant; } ;
typedef  int /*<<< orphan*/  ip_set_id_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* uref ) (struct ip_set*,struct netlink_callback*,int) ;} ;

/* Variables and functions */
 size_t IPSET_CB_ARG0 ; 
 size_t IPSET_CB_INDEX ; 
 size_t IPSET_CB_NET ; 
 int /*<<< orphan*/  __ip_set_put_netlink (struct ip_set*) ; 
 struct ip_set* ip_set_ref_netlink (struct ip_set_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ip_set*,struct netlink_callback*,int) ; 

__attribute__((used)) static int
ip_set_dump_done(struct netlink_callback *cb)
{
	if (cb->args[IPSET_CB_ARG0]) {
		struct ip_set_net *inst =
			(struct ip_set_net *)cb->args[IPSET_CB_NET];
		ip_set_id_t index = (ip_set_id_t)cb->args[IPSET_CB_INDEX];
		struct ip_set *set = ip_set_ref_netlink(inst, index);

		if (set->variant->uref)
			set->variant->uref(set, cb, false);
		pr_debug("release set %s\n", set->name);
		__ip_set_put_netlink(set);
	}
	return 0;
}