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
typedef  union rds_ib_conn_priv {int dummy; } rds_ib_conn_priv ;
struct rds_ib_connection {int i_active_side; struct rdma_cm_id* i_cm_id; int /*<<< orphan*/  i_flowctl; } ;
struct rds_connection {int /*<<< orphan*/  c_proposed_version; struct rds_ib_connection* c_transport_data; } ;
struct rdma_conn_param {int dummy; } ;
struct rdma_cm_id {struct rds_connection* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_PROTOCOL_4_1 ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int rdma_connect (struct rdma_cm_id*,struct rdma_conn_param*) ; 
 int /*<<< orphan*/  rds_ib_cm_fill_conn_param (struct rds_connection*,struct rdma_conn_param*,union rds_ib_conn_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rds_ib_conn_error (struct rds_connection*,char*,int) ; 
 int /*<<< orphan*/  rds_ib_set_protocol (struct rds_connection*,int /*<<< orphan*/ ) ; 
 int rds_ib_setup_qp (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_sysctl_flow_control ; 

int rds_ib_cm_initiate_connect(struct rdma_cm_id *cm_id, bool isv6)
{
	struct rds_connection *conn = cm_id->context;
	struct rds_ib_connection *ic = conn->c_transport_data;
	struct rdma_conn_param conn_param;
	union rds_ib_conn_priv dp;
	int ret;

	/* If the peer doesn't do protocol negotiation, we must
	 * default to RDSv3.0 */
	rds_ib_set_protocol(conn, RDS_PROTOCOL_4_1);
	ic->i_flowctl = rds_ib_sysctl_flow_control;	/* advertise flow control */

	ret = rds_ib_setup_qp(conn);
	if (ret) {
		rds_ib_conn_error(conn, "rds_ib_setup_qp failed (%d)\n", ret);
		goto out;
	}

	rds_ib_cm_fill_conn_param(conn, &conn_param, &dp,
				  conn->c_proposed_version,
				  UINT_MAX, UINT_MAX, isv6);
	ret = rdma_connect(cm_id, &conn_param);
	if (ret)
		rds_ib_conn_error(conn, "rdma_connect failed (%d)\n", ret);

out:
	/* Beware - returning non-zero tells the rdma_cm to destroy
	 * the cm_id. We should certainly not do it as long as we still
	 * "own" the cm_id. */
	if (ret) {
		if (ic->i_cm_id == cm_id)
			ret = 0;
	}
	ic->i_active_side = true;
	return ret;
}