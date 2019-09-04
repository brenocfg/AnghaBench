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
struct socket {TYPE_1__* sk; } ;
struct rds_tcp_net {struct socket* rds_tcp_listen_sock; } ;
struct net {int dummy; } ;
struct TYPE_2__ {void* sk_user_data; } ;

/* Variables and functions */
 struct rds_tcp_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_tcp_netid ; 

void *rds_tcp_listen_sock_def_readable(struct net *net)
{
	struct rds_tcp_net *rtn = net_generic(net, rds_tcp_netid);
	struct socket *lsock = rtn->rds_tcp_listen_sock;

	if (!lsock)
		return NULL;

	return lsock->sk->sk_user_data;
}