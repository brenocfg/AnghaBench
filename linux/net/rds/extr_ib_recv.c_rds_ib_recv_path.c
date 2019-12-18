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
struct rds_ib_connection {int dummy; } ;
struct rds_connection {struct rds_ib_connection* c_transport_data; } ;
struct rds_conn_path {struct rds_connection* cp_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ rds_conn_up (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_attempt_ack (struct rds_ib_connection*) ; 
 int /*<<< orphan*/  rds_ib_recv_refill (struct rds_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_connection*) ; 
 int /*<<< orphan*/  s_ib_rx_refill_from_thread ; 

int rds_ib_recv_path(struct rds_conn_path *cp)
{
	struct rds_connection *conn = cp->cp_conn;
	struct rds_ib_connection *ic = conn->c_transport_data;

	rdsdebug("conn %p\n", conn);
	if (rds_conn_up(conn)) {
		rds_ib_attempt_ack(ic);
		rds_ib_recv_refill(conn, 0, GFP_KERNEL);
		rds_ib_stats_inc(s_ib_rx_refill_from_thread);
	}

	return 0;
}