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
struct tipc_topsrv {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  conn_idr; } ;
struct tipc_conn {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  connected (struct tipc_conn*) ; 
 struct tipc_conn* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tipc_conn *tipc_conn_lookup(struct tipc_topsrv *s, int conid)
{
	struct tipc_conn *con;

	spin_lock_bh(&s->idr_lock);
	con = idr_find(&s->conn_idr, conid);
	if (!connected(con) || !kref_get_unless_zero(&con->kref))
		con = NULL;
	spin_unlock_bh(&s->idr_lock);
	return con;
}