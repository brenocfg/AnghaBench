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
struct rds_connection {int /*<<< orphan*/  c_proposed_version; } ;
struct rds_conn_path {int cp_next_tx_seq; scalar_t__ cp_flags; int /*<<< orphan*/  cp_cm_lock; int /*<<< orphan*/  cp_down_w; int /*<<< orphan*/  cp_conn_w; int /*<<< orphan*/  cp_recv_w; int /*<<< orphan*/  cp_send_w; struct rds_connection* cp_conn; scalar_t__ cp_reconnect_jiffies; scalar_t__ cp_send_gen; int /*<<< orphan*/  cp_state; int /*<<< orphan*/  cp_retrans; int /*<<< orphan*/  cp_send_queue; int /*<<< orphan*/  cp_waitq; int /*<<< orphan*/  cp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDS_CONN_DOWN ; 
 int /*<<< orphan*/  RDS_PROTOCOL_VERSION ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_connect_worker ; 
 int /*<<< orphan*/  rds_recv_worker ; 
 int /*<<< orphan*/  rds_send_worker ; 
 int /*<<< orphan*/  rds_shutdown_worker ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rds_conn_path_init(struct rds_connection *conn,
				 struct rds_conn_path *cp, bool is_outgoing)
{
	spin_lock_init(&cp->cp_lock);
	cp->cp_next_tx_seq = 1;
	init_waitqueue_head(&cp->cp_waitq);
	INIT_LIST_HEAD(&cp->cp_send_queue);
	INIT_LIST_HEAD(&cp->cp_retrans);

	cp->cp_conn = conn;
	atomic_set(&cp->cp_state, RDS_CONN_DOWN);
	cp->cp_send_gen = 0;
	cp->cp_reconnect_jiffies = 0;
	cp->cp_conn->c_proposed_version = RDS_PROTOCOL_VERSION;
	INIT_DELAYED_WORK(&cp->cp_send_w, rds_send_worker);
	INIT_DELAYED_WORK(&cp->cp_recv_w, rds_recv_worker);
	INIT_DELAYED_WORK(&cp->cp_conn_w, rds_connect_worker);
	INIT_WORK(&cp->cp_down_w, rds_shutdown_worker);
	mutex_init(&cp->cp_cm_lock);
	cp->cp_flags = 0;
}