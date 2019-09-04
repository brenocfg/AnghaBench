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
struct rds_tcp_connection {int t_tinc_hdr_rem; int t_tcp_node_detached; int /*<<< orphan*/  t_tcp_node; TYPE_1__* t_cpath; scalar_t__ t_tinc_data_rem; int /*<<< orphan*/ * t_tinc; int /*<<< orphan*/ * t_sock; int /*<<< orphan*/  t_conn_path_lock; } ;
struct rds_header {int dummy; } ;
struct rds_connection {TYPE_1__* c_path; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct rds_tcp_connection* cp_transport_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int RDS_MPATH_WORKERS ; 
 struct rds_tcp_connection* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_tcp_conn_free (struct rds_tcp_connection*) ; 
 int /*<<< orphan*/  rds_tcp_conn_list ; 
 int /*<<< orphan*/  rds_tcp_conn_lock ; 
 int /*<<< orphan*/  rds_tcp_conn_slab ; 
 int /*<<< orphan*/  rdsdebug (char*,int,struct rds_tcp_connection*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rds_tcp_conn_alloc(struct rds_connection *conn, gfp_t gfp)
{
	struct rds_tcp_connection *tc;
	int i, j;
	int ret = 0;

	for (i = 0; i < RDS_MPATH_WORKERS; i++) {
		tc = kmem_cache_alloc(rds_tcp_conn_slab, gfp);
		if (!tc) {
			ret = -ENOMEM;
			goto fail;
		}
		mutex_init(&tc->t_conn_path_lock);
		tc->t_sock = NULL;
		tc->t_tinc = NULL;
		tc->t_tinc_hdr_rem = sizeof(struct rds_header);
		tc->t_tinc_data_rem = 0;

		conn->c_path[i].cp_transport_data = tc;
		tc->t_cpath = &conn->c_path[i];
		tc->t_tcp_node_detached = true;

		rdsdebug("rds_conn_path [%d] tc %p\n", i,
			 conn->c_path[i].cp_transport_data);
	}
	spin_lock_irq(&rds_tcp_conn_lock);
	for (i = 0; i < RDS_MPATH_WORKERS; i++) {
		tc = conn->c_path[i].cp_transport_data;
		tc->t_tcp_node_detached = false;
		list_add_tail(&tc->t_tcp_node, &rds_tcp_conn_list);
	}
	spin_unlock_irq(&rds_tcp_conn_lock);
fail:
	if (ret) {
		for (j = 0; j < i; j++)
			rds_tcp_conn_free(conn->c_path[j].cp_transport_data);
	}
	return ret;
}