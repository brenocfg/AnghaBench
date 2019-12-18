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
struct rds_connection {int /*<<< orphan*/  c_faddr; int /*<<< orphan*/  c_laddr; } ;
struct rds_conn_path {scalar_t__ cp_flags; struct rds_connection* cp_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  rds_send_path_reset (struct rds_conn_path*) ; 
 int /*<<< orphan*/  rds_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_conn_reset ; 

__attribute__((used)) static void rds_conn_path_reset(struct rds_conn_path *cp)
{
	struct rds_connection *conn = cp->cp_conn;

	rdsdebug("connection %pI6c to %pI6c reset\n",
		 &conn->c_laddr, &conn->c_faddr);

	rds_stats_inc(s_conn_reset);
	rds_send_path_reset(cp);
	cp->cp_flags = 0;

	/* Do not clear next_rx_seq here, else we cannot distinguish
	 * retransmitted packets from new packets, and will hand all
	 * of them to the application. That is not consistent with the
	 * reliability guarantees of RDS. */
}