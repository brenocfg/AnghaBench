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
struct xt_rateest_net {int /*<<< orphan*/  hash_lock; } ;
struct xt_rateest {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct xt_rateest* __xt_rateest_lookup (struct xt_rateest_net*,char const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct xt_rateest_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_rateest_id ; 

struct xt_rateest *xt_rateest_lookup(struct net *net, const char *name)
{
	struct xt_rateest_net *xn = net_generic(net, xt_rateest_id);
	struct xt_rateest *est;

	mutex_lock(&xn->hash_lock);
	est = __xt_rateest_lookup(xn, name);
	mutex_unlock(&xn->hash_lock);
	return est;
}