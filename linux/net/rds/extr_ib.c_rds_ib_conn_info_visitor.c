#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
struct rds_info_rdma_connection {int /*<<< orphan*/  cache_allocs; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  dst_gid; int /*<<< orphan*/  src_gid; int /*<<< orphan*/  sl; int /*<<< orphan*/  tos; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct rds_ib_device {int /*<<< orphan*/  max_sge; } ;
struct TYPE_8__ {int /*<<< orphan*/  w_nr; } ;
struct TYPE_7__ {int /*<<< orphan*/  w_nr; } ;
struct rds_ib_connection {int /*<<< orphan*/  i_cache_allocs; TYPE_4__ i_recv_ring; TYPE_3__ i_send_ring; struct rds_ib_device* rds_ibdev; int /*<<< orphan*/  i_cm_id; int /*<<< orphan*/  i_sl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * s6_addr32; } ;
struct TYPE_5__ {int /*<<< orphan*/ * s6_addr32; } ;
struct rds_connection {int /*<<< orphan*/  c_tos; TYPE_2__ c_faddr; TYPE_1__ c_laddr; scalar_t__ c_isv6; int /*<<< orphan*/ * c_trans; struct rds_ib_connection* c_transport_data; } ;

/* Variables and functions */
 scalar_t__ RDS_CONN_UP ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_read_gids (int /*<<< orphan*/ ,union ib_gid*,union ib_gid*) ; 
 scalar_t__ rds_conn_state (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_get_mr_info (struct rds_ib_device*,struct rds_info_rdma_connection*) ; 
 int /*<<< orphan*/  rds_ib_transport ; 

__attribute__((used)) static int rds_ib_conn_info_visitor(struct rds_connection *conn,
				    void *buffer)
{
	struct rds_info_rdma_connection *iinfo = buffer;
	struct rds_ib_connection *ic = conn->c_transport_data;

	/* We will only ever look at IB transports */
	if (conn->c_trans != &rds_ib_transport)
		return 0;
	if (conn->c_isv6)
		return 0;

	iinfo->src_addr = conn->c_laddr.s6_addr32[3];
	iinfo->dst_addr = conn->c_faddr.s6_addr32[3];
	if (ic) {
		iinfo->tos = conn->c_tos;
		iinfo->sl = ic->i_sl;
	}

	memset(&iinfo->src_gid, 0, sizeof(iinfo->src_gid));
	memset(&iinfo->dst_gid, 0, sizeof(iinfo->dst_gid));
	if (rds_conn_state(conn) == RDS_CONN_UP) {
		struct rds_ib_device *rds_ibdev;

		rdma_read_gids(ic->i_cm_id, (union ib_gid *)&iinfo->src_gid,
			       (union ib_gid *)&iinfo->dst_gid);

		rds_ibdev = ic->rds_ibdev;
		iinfo->max_send_wr = ic->i_send_ring.w_nr;
		iinfo->max_recv_wr = ic->i_recv_ring.w_nr;
		iinfo->max_send_sge = rds_ibdev->max_sge;
		rds_ib_get_mr_info(rds_ibdev, iinfo);
		iinfo->cache_allocs = atomic_read(&ic->i_cache_allocs);
	}
	return 1;
}