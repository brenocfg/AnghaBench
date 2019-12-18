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
struct rds_loop_connection {int /*<<< orphan*/  loop_node; struct rds_connection* conn; } ;
struct rds_connection {struct rds_loop_connection* c_transport_data; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct rds_loop_connection* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop_conns ; 
 int /*<<< orphan*/  loop_conns_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rds_loop_conn_alloc(struct rds_connection *conn, gfp_t gfp)
{
	struct rds_loop_connection *lc;
	unsigned long flags;

	lc = kzalloc(sizeof(struct rds_loop_connection), gfp);
	if (!lc)
		return -ENOMEM;

	INIT_LIST_HEAD(&lc->loop_node);
	lc->conn = conn;
	conn->c_transport_data = lc;

	spin_lock_irqsave(&loop_conns_lock, flags);
	list_add_tail(&lc->loop_node, &loop_conns);
	spin_unlock_irqrestore(&loop_conns_lock, flags);

	return 0;
}