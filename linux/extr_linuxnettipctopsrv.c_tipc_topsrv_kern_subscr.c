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
typedef  void* u32 ;
struct TYPE_2__ {void* upper; void* lower; void* type; } ;
struct tipc_subscr {int /*<<< orphan*/  usr_handle; void* filter; int /*<<< orphan*/  timeout; TYPE_1__ seq; } ;
struct tipc_conn {int conid; int /*<<< orphan*/ * sock; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tipc_conn*) ; 
 int /*<<< orphan*/  TIPC_WAIT_FOREVER ; 
 int /*<<< orphan*/  conn_put (struct tipc_conn*) ; 
 struct tipc_conn* tipc_conn_alloc (int /*<<< orphan*/ ) ; 
 int tipc_conn_rcv_sub (int /*<<< orphan*/ ,struct tipc_conn*,struct tipc_subscr*) ; 
 int /*<<< orphan*/  tipc_topsrv (struct net*) ; 

bool tipc_topsrv_kern_subscr(struct net *net, u32 port, u32 type, u32 lower,
			     u32 upper, u32 filter, int *conid)
{
	struct tipc_subscr sub;
	struct tipc_conn *con;
	int rc;

	sub.seq.type = type;
	sub.seq.lower = lower;
	sub.seq.upper = upper;
	sub.timeout = TIPC_WAIT_FOREVER;
	sub.filter = filter;
	*(u32 *)&sub.usr_handle = port;

	con = tipc_conn_alloc(tipc_topsrv(net));
	if (IS_ERR(con))
		return false;

	*conid = con->conid;
	con->sock = NULL;
	rc = tipc_conn_rcv_sub(tipc_topsrv(net), con, &sub);
	if (rc >= 0)
		return true;
	conn_put(con);
	return false;
}