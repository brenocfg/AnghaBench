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
typedef  int /*<<< orphan*/  u32 ;
struct sockaddr_in6 {void* sin6_port; } ;
struct sockaddr_in {void* sin_port; } ;
struct sockaddr {int sa_family; } ;
struct rpc_create_args {int protocol; size_t addrsize; char const* servername; char const* nodename; int flags; struct cred const* cred; int /*<<< orphan*/  authflavor; int /*<<< orphan*/  version; int /*<<< orphan*/ * program; struct sockaddr* address; struct net* net; } ;
struct rpc_clnt {int dummy; } ;
struct net {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 struct rpc_clnt* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCBIND_PORT ; 
 int /*<<< orphan*/  RPC_AUTH_UNIX ; 
 int RPC_CLNT_CREATE_NONPRIVPORT ; 
 int RPC_CLNT_CREATE_NOPING ; 
 void* htons (int /*<<< orphan*/ ) ; 
 struct rpc_clnt* rpc_create (struct rpc_create_args*) ; 
 int /*<<< orphan*/  rpcb_program ; 

__attribute__((used)) static struct rpc_clnt *rpcb_create(struct net *net, const char *nodename,
				    const char *hostname,
				    struct sockaddr *srvaddr, size_t salen,
				    int proto, u32 version,
				    const struct cred *cred)
{
	struct rpc_create_args args = {
		.net		= net,
		.protocol	= proto,
		.address	= srvaddr,
		.addrsize	= salen,
		.servername	= hostname,
		.nodename	= nodename,
		.program	= &rpcb_program,
		.version	= version,
		.authflavor	= RPC_AUTH_UNIX,
		.cred		= cred,
		.flags		= (RPC_CLNT_CREATE_NOPING |
					RPC_CLNT_CREATE_NONPRIVPORT),
	};

	switch (srvaddr->sa_family) {
	case AF_INET:
		((struct sockaddr_in *)srvaddr)->sin_port = htons(RPCBIND_PORT);
		break;
	case AF_INET6:
		((struct sockaddr_in6 *)srvaddr)->sin6_port = htons(RPCBIND_PORT);
		break;
	default:
		return ERR_PTR(-EAFNOSUPPORT);
	}

	return rpc_create(&args);
}