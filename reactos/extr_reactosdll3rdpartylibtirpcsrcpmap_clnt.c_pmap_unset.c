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
typedef  scalar_t__ u_long ;
struct netconfig {int dummy; } ;
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;
typedef  int bool_t ;

/* Variables and functions */
 int FALSE ; 
 struct netconfig* __rpc_getconfip (char*) ; 
 int /*<<< orphan*/  freenetconfigent (struct netconfig*) ; 
 int rpcb_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netconfig*) ; 

bool_t
pmap_unset(u_long program, u_long version)
{
	struct netconfig *nconf;
	bool_t udp_rslt = FALSE;
	bool_t tcp_rslt = FALSE;

	nconf = __rpc_getconfip("udp");
	if (nconf != NULL) {
		udp_rslt = rpcb_unset((rpcprog_t)program, (rpcvers_t)version,
		    nconf);
		freenetconfigent(nconf);
	}
	nconf = __rpc_getconfip("tcp");
	if (nconf != NULL) {
		tcp_rslt = rpcb_unset((rpcprog_t)program, (rpcvers_t)version,
		    nconf);
		freenetconfigent(nconf);
	}
	/*
	 * XXX: The call may still succeed even if only one of the
	 * calls succeeded.  This was the best that could be
	 * done for backward compatibility.
	 */
	return (tcp_rslt || udp_rslt);
}