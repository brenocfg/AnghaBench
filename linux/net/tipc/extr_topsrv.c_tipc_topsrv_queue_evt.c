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
typedef  scalar_t__ u32 ;
struct tipc_topsrv {int /*<<< orphan*/  send_wq; } ;
struct tipc_event {int dummy; } ;
struct tipc_conn {int /*<<< orphan*/  swork; int /*<<< orphan*/  outqueue_lock; int /*<<< orphan*/  outqueue; } ;
struct outqueue_entry {int inactive; int /*<<< orphan*/  list; int /*<<< orphan*/  evt; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ TIPC_SUBSCR_TIMEOUT ; 
 int /*<<< orphan*/  conn_put (struct tipc_conn*) ; 
 int /*<<< orphan*/  connected (struct tipc_conn*) ; 
 struct outqueue_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct tipc_event*,int) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct tipc_conn* tipc_conn_lookup (struct tipc_topsrv*,int) ; 
 struct tipc_topsrv* tipc_topsrv (struct net*) ; 

void tipc_topsrv_queue_evt(struct net *net, int conid,
			   u32 event, struct tipc_event *evt)
{
	struct tipc_topsrv *srv = tipc_topsrv(net);
	struct outqueue_entry *e;
	struct tipc_conn *con;

	con = tipc_conn_lookup(srv, conid);
	if (!con)
		return;

	if (!connected(con))
		goto err;

	e = kmalloc(sizeof(*e), GFP_ATOMIC);
	if (!e)
		goto err;
	e->inactive = (event == TIPC_SUBSCR_TIMEOUT);
	memcpy(&e->evt, evt, sizeof(*evt));
	spin_lock_bh(&con->outqueue_lock);
	list_add_tail(&e->list, &con->outqueue);
	spin_unlock_bh(&con->outqueue_lock);

	if (queue_work(srv->send_wq, &con->swork))
		return;
err:
	conn_put(con);
}