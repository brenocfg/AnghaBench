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
struct TYPE_2__ {int /*<<< orphan*/  fib6_main_tbl; struct fib6_info* fib6_null_entry; int /*<<< orphan*/  fib6_local_tbl; int /*<<< orphan*/  fib6_rules_ops; scalar_t__ fib6_has_custom_rules; } ;
struct net {TYPE_1__ ipv6; } ;
struct flowi6 {int dummy; } ;
struct fib_lookup_arg {int* lookup_data; scalar_t__ result; int /*<<< orphan*/  flags; struct fib6_info* (* lookup_ptr ) (struct net*,int /*<<< orphan*/ ,int,struct flowi6*,int) ;} ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 struct fib6_info* ERR_PTR (int) ; 
 int /*<<< orphan*/  FIB_LOOKUP_NOREF ; 
 struct fib6_info* fib6_table_lookup (struct net*,int /*<<< orphan*/ ,int,struct flowi6*,int) ; 
 int fib_rules_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fib_lookup_arg*) ; 
 int /*<<< orphan*/  flowi6_to_flowi (struct flowi6*) ; 
 int /*<<< orphan*/  l3mdev_update_flow (struct net*,int /*<<< orphan*/ ) ; 

struct fib6_info *fib6_lookup(struct net *net, int oif, struct flowi6 *fl6,
			      int flags)
{
	struct fib6_info *f6i;
	int err;

	if (net->ipv6.fib6_has_custom_rules) {
		struct fib_lookup_arg arg = {
			.lookup_ptr = fib6_table_lookup,
			.lookup_data = &oif,
			.flags = FIB_LOOKUP_NOREF,
		};

		l3mdev_update_flow(net, flowi6_to_flowi(fl6));

		err = fib_rules_lookup(net->ipv6.fib6_rules_ops,
				       flowi6_to_flowi(fl6), flags, &arg);
		if (err)
			return ERR_PTR(err);

		f6i = arg.result ? : net->ipv6.fib6_null_entry;
	} else {
		f6i = fib6_table_lookup(net, net->ipv6.fib6_local_tbl,
					oif, fl6, flags);
		if (!f6i || f6i == net->ipv6.fib6_null_entry)
			f6i = fib6_table_lookup(net, net->ipv6.fib6_main_tbl,
						oif, fl6, flags);
	}

	return f6i;
}