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
struct tipc_topsrv {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  idr_in_use; int /*<<< orphan*/  conn_idr; } ;
struct tipc_conn {int conid; struct tipc_topsrv* server; int /*<<< orphan*/  flags; int /*<<< orphan*/  rwork; int /*<<< orphan*/  swork; int /*<<< orphan*/  sub_lock; int /*<<< orphan*/  outqueue_lock; int /*<<< orphan*/  sub_list; int /*<<< orphan*/  outqueue; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CONNECTED ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct tipc_conn* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct tipc_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tipc_conn*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct tipc_conn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_conn_recv_work ; 
 int /*<<< orphan*/  tipc_conn_send_work ; 

__attribute__((used)) static struct tipc_conn *tipc_conn_alloc(struct tipc_topsrv *s)
{
	struct tipc_conn *con;
	int ret;

	con = kzalloc(sizeof(*con), GFP_ATOMIC);
	if (!con)
		return ERR_PTR(-ENOMEM);

	kref_init(&con->kref);
	INIT_LIST_HEAD(&con->outqueue);
	INIT_LIST_HEAD(&con->sub_list);
	spin_lock_init(&con->outqueue_lock);
	spin_lock_init(&con->sub_lock);
	INIT_WORK(&con->swork, tipc_conn_send_work);
	INIT_WORK(&con->rwork, tipc_conn_recv_work);

	spin_lock_bh(&s->idr_lock);
	ret = idr_alloc(&s->conn_idr, con, 0, 0, GFP_ATOMIC);
	if (ret < 0) {
		kfree(con);
		spin_unlock_bh(&s->idr_lock);
		return ERR_PTR(-ENOMEM);
	}
	con->conid = ret;
	s->idr_in_use++;
	spin_unlock_bh(&s->idr_lock);

	set_bit(CF_CONNECTED, &con->flags);
	con->server = s;

	return con;
}