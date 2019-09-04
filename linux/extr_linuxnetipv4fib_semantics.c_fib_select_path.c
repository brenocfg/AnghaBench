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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct flowi4 {int flowi4_flags; scalar_t__ saddr; scalar_t__ flowi4_oif; } ;
struct fib_result {scalar_t__ type; TYPE_1__* table; int /*<<< orphan*/  prefixlen; } ;
struct TYPE_2__ {int tb_num_default; } ;

/* Variables and functions */
 scalar_t__ FIB_RES_PREFSRC (struct net*,struct fib_result) ; 
 int FLOWI_FLAG_SKIP_NH_OIF ; 
 scalar_t__ RTN_UNICAST ; 
 int /*<<< orphan*/  fib_select_default (struct flowi4*,struct fib_result*) ; 

void fib_select_path(struct net *net, struct fib_result *res,
		     struct flowi4 *fl4, const struct sk_buff *skb)
{
	if (fl4->flowi4_oif && !(fl4->flowi4_flags & FLOWI_FLAG_SKIP_NH_OIF))
		goto check_saddr;

#ifdef CONFIG_IP_ROUTE_MULTIPATH
	if (res->fi->fib_nhs > 1) {
		int h = fib_multipath_hash(net, fl4, skb, NULL);

		fib_select_multipath(res, h);
	}
	else
#endif
	if (!res->prefixlen &&
	    res->table->tb_num_default > 1 &&
	    res->type == RTN_UNICAST)
		fib_select_default(fl4, res);

check_saddr:
	if (!fl4->saddr)
		fl4->saddr = FIB_RES_PREFSRC(net, *res);
}