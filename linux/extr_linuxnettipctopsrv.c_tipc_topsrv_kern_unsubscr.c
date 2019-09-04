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
struct tipc_conn {int /*<<< orphan*/  flags; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CONNECTED ; 
 int /*<<< orphan*/  conn_put (struct tipc_conn*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_conn_delete_sub (struct tipc_conn*,int /*<<< orphan*/ *) ; 
 struct tipc_conn* tipc_conn_lookup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tipc_topsrv (struct net*) ; 

void tipc_topsrv_kern_unsubscr(struct net *net, int conid)
{
	struct tipc_conn *con;

	con = tipc_conn_lookup(tipc_topsrv(net), conid);
	if (!con)
		return;

	test_and_clear_bit(CF_CONNECTED, &con->flags);
	tipc_conn_delete_sub(con, NULL);
	conn_put(con);
	conn_put(con);
}