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
struct rds_connection {TYPE_1__* c_lcong; int /*<<< orphan*/  c_map_item; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_conn_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_cong_lock ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_connection*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rds_cong_add_conn(struct rds_connection *conn)
{
	unsigned long flags;

	rdsdebug("conn %p now on map %p\n", conn, conn->c_lcong);
	spin_lock_irqsave(&rds_cong_lock, flags);
	list_add_tail(&conn->c_map_item, &conn->c_lcong->m_conn_list);
	spin_unlock_irqrestore(&rds_cong_lock, flags);
}