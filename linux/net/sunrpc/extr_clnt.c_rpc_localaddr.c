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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct rpc_xprt {size_t addrlen; int /*<<< orphan*/  xprt_net; int /*<<< orphan*/  addr; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_xprt; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct net* get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 struct rpc_xprt* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int rpc_anyaddr (int /*<<< orphan*/ ,struct sockaddr*,size_t) ; 
 int /*<<< orphan*/  rpc_set_port (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int rpc_sockname (struct net*,struct sockaddr*,size_t,struct sockaddr*) ; 

int rpc_localaddr(struct rpc_clnt *clnt, struct sockaddr *buf, size_t buflen)
{
	struct sockaddr_storage address;
	struct sockaddr *sap = (struct sockaddr *)&address;
	struct rpc_xprt *xprt;
	struct net *net;
	size_t salen;
	int err;

	rcu_read_lock();
	xprt = rcu_dereference(clnt->cl_xprt);
	salen = xprt->addrlen;
	memcpy(sap, &xprt->addr, salen);
	net = get_net(xprt->xprt_net);
	rcu_read_unlock();

	rpc_set_port(sap, 0);
	err = rpc_sockname(net, sap, salen, buf);
	put_net(net);
	if (err != 0)
		/* Couldn't discover local address, return ANYADDR */
		return rpc_anyaddr(sap->sa_family, buf, buflen);
	return 0;
}