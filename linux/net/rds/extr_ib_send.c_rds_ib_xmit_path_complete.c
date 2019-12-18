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
 int /*<<< orphan*/  rds_ib_attempt_ack (struct rds_ib_connection*) ; 

void rds_ib_xmit_path_complete(struct rds_conn_path *cp)
{
	struct rds_connection *conn = cp->cp_conn;
	struct rds_ib_connection *ic = conn->c_transport_data;

	/* We may have a pending ACK or window update we were unable
	 * to send previously (due to flow control). Try again. */
	rds_ib_attempt_ack(ic);
}