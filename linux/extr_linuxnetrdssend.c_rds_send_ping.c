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
struct rds_connection {int c_ping_triggered; struct rds_conn_path* c_path; } ;
struct rds_conn_path {int /*<<< orphan*/  cp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_FLAG_PROBE_PORT ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_send_probe (struct rds_conn_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
rds_send_ping(struct rds_connection *conn, int cp_index)
{
	unsigned long flags;
	struct rds_conn_path *cp = &conn->c_path[cp_index];

	spin_lock_irqsave(&cp->cp_lock, flags);
	if (conn->c_ping_triggered) {
		spin_unlock_irqrestore(&cp->cp_lock, flags);
		return;
	}
	conn->c_ping_triggered = 1;
	spin_unlock_irqrestore(&cp->cp_lock, flags);
	rds_send_probe(cp, cpu_to_be16(RDS_FLAG_PROBE_PORT), 0, 0);
}