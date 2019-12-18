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
struct sock {int dummy; } ;
struct rds_tcp_net {int /*<<< orphan*/  rds_tcp_accept_w; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct rds_tcp_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_tcp_netid ; 
 int /*<<< orphan*/  rds_wq ; 
 struct net* sock_net (struct sock*) ; 

void rds_tcp_accept_work(struct sock *sk)
{
	struct net *net = sock_net(sk);
	struct rds_tcp_net *rtn = net_generic(net, rds_tcp_netid);

	queue_work(rds_wq, &rtn->rds_tcp_accept_w);
}