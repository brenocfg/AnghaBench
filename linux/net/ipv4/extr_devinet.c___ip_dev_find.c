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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct in_ifaddr {TYPE_1__* ifa_dev; } ;
struct flowi4 {int /*<<< orphan*/  daddr; } ;
struct fib_table {int dummy; } ;
struct fib_result {scalar_t__ type; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIB_LOOKUP_NOREF ; 
 struct net_device* FIB_RES_DEV (struct fib_result) ; 
 scalar_t__ RTN_LOCAL ; 
 int /*<<< orphan*/  RT_TABLE_LOCAL ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct fib_table* fib_get_table (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib_table_lookup (struct fib_table*,struct flowi4*,struct fib_result*,int /*<<< orphan*/ ) ; 
 struct in_ifaddr* inet_lookup_ifaddr_rcu (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct net_device *__ip_dev_find(struct net *net, __be32 addr, bool devref)
{
	struct net_device *result = NULL;
	struct in_ifaddr *ifa;

	rcu_read_lock();
	ifa = inet_lookup_ifaddr_rcu(net, addr);
	if (!ifa) {
		struct flowi4 fl4 = { .daddr = addr };
		struct fib_result res = { 0 };
		struct fib_table *local;

		/* Fallback to FIB local table so that communication
		 * over loopback subnets work.
		 */
		local = fib_get_table(net, RT_TABLE_LOCAL);
		if (local &&
		    !fib_table_lookup(local, &fl4, &res, FIB_LOOKUP_NOREF) &&
		    res.type == RTN_LOCAL)
			result = FIB_RES_DEV(res);
	} else {
		result = ifa->ifa_dev->dev;
	}
	if (result && devref)
		dev_hold(result);
	rcu_read_unlock();
	return result;
}