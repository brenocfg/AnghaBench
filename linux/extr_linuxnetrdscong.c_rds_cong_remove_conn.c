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
struct rds_connection {int /*<<< orphan*/  c_map_item; int /*<<< orphan*/  c_lcong; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_cong_lock ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rds_cong_remove_conn(struct rds_connection *conn)
{
	unsigned long flags;

	rdsdebug("removing conn %p from map %p\n", conn, conn->c_lcong);
	spin_lock_irqsave(&rds_cong_lock, flags);
	list_del_init(&conn->c_map_item);
	spin_unlock_irqrestore(&rds_cong_lock, flags);
}