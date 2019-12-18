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
struct net {int dummy; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct datapath* get_dp_rcu (struct net*,int) ; 
 int /*<<< orphan*/  lockdep_ovsl_is_held () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline struct datapath *get_dp(struct net *net, int dp_ifindex)
{
	struct datapath *dp;

	WARN_ON_ONCE(!rcu_read_lock_held() && !lockdep_ovsl_is_held());
	rcu_read_lock();
	dp = get_dp_rcu(net, dp_ifindex);
	rcu_read_unlock();

	return dp;
}