#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct nsim_fib_entry {scalar_t__ num; scalar_t__ max; } ;
struct TYPE_3__ {struct nsim_fib_entry rules; struct nsim_fib_entry fib; } ;
struct TYPE_4__ {struct nsim_fib_entry rules; struct nsim_fib_entry fib; } ;
struct nsim_fib_data {TYPE_1__ ipv6; TYPE_2__ ipv4; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
typedef  enum nsim_resource_id { ____Placeholder_nsim_resource_id } nsim_resource_id ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
#define  NSIM_RESOURCE_IPV4_FIB 131 
#define  NSIM_RESOURCE_IPV4_FIB_RULES 130 
#define  NSIM_RESOURCE_IPV6_FIB 129 
#define  NSIM_RESOURCE_IPV6_FIB_RULES 128 
 struct nsim_fib_data* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_fib_net_id ; 

int nsim_fib_set_max(struct net *net, enum nsim_resource_id res_id, u64 val,
		     struct netlink_ext_ack *extack)
{
	struct nsim_fib_data *fib_data = net_generic(net, nsim_fib_net_id);
	struct nsim_fib_entry *entry;
	int err = 0;

	switch (res_id) {
	case NSIM_RESOURCE_IPV4_FIB:
		entry = &fib_data->ipv4.fib;
		break;
	case NSIM_RESOURCE_IPV4_FIB_RULES:
		entry = &fib_data->ipv4.rules;
		break;
	case NSIM_RESOURCE_IPV6_FIB:
		entry = &fib_data->ipv6.fib;
		break;
	case NSIM_RESOURCE_IPV6_FIB_RULES:
		entry = &fib_data->ipv6.rules;
		break;
	default:
		return 0;
	}

	/* not allowing a new max to be less than curren occupancy
	 * --> no means of evicting entries
	 */
	if (val < entry->num) {
		NL_SET_ERR_MSG_MOD(extack, "New size is less than current occupancy");
		err = -EINVAL;
	} else {
		entry->max = val;
	}

	return err;
}