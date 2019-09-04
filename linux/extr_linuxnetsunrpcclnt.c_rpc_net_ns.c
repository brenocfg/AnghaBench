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
struct rpc_clnt {int /*<<< orphan*/  cl_xprt; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct net* xprt_net; } ;

/* Variables and functions */
 TYPE_1__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct net *rpc_net_ns(struct rpc_clnt *clnt)
{
	struct net *ret;

	rcu_read_lock();
	ret = rcu_dereference(clnt->cl_xprt)->xprt_net;
	rcu_read_unlock();
	return ret;
}