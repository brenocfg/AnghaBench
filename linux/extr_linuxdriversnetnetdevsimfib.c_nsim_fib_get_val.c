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
typedef  int /*<<< orphan*/  u64 ;
struct nsim_fib_entry {int /*<<< orphan*/  num; int /*<<< orphan*/  max; } ;
struct TYPE_4__ {struct nsim_fib_entry rules; struct nsim_fib_entry fib; } ;
struct TYPE_3__ {struct nsim_fib_entry rules; struct nsim_fib_entry fib; } ;
struct nsim_fib_data {TYPE_2__ ipv6; TYPE_1__ ipv4; } ;
struct net {int dummy; } ;
typedef  enum nsim_resource_id { ____Placeholder_nsim_resource_id } nsim_resource_id ;

/* Variables and functions */
#define  NSIM_RESOURCE_IPV4_FIB 131 
#define  NSIM_RESOURCE_IPV4_FIB_RULES 130 
#define  NSIM_RESOURCE_IPV6_FIB 129 
#define  NSIM_RESOURCE_IPV6_FIB_RULES 128 
 struct nsim_fib_data* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_fib_net_id ; 

u64 nsim_fib_get_val(struct net *net, enum nsim_resource_id res_id, bool max)
{
	struct nsim_fib_data *fib_data = net_generic(net, nsim_fib_net_id);
	struct nsim_fib_entry *entry;

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

	return max ? entry->max : entry->num;
}