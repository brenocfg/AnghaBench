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
struct TYPE_2__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct in6_addr {int dummy; } ;
struct rds_incoming {scalar_t__* i_rx_lat_trace; TYPE_1__ i_rx_tstamp; scalar_t__ i_rdma_cookie; struct in6_addr i_saddr; struct rds_connection* i_conn; int /*<<< orphan*/  i_item; int /*<<< orphan*/  i_refcount; } ;
struct rds_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int RDS_RX_MAX_TRACES ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

void rds_inc_init(struct rds_incoming *inc, struct rds_connection *conn,
		 struct in6_addr *saddr)
{
	int i;

	refcount_set(&inc->i_refcount, 1);
	INIT_LIST_HEAD(&inc->i_item);
	inc->i_conn = conn;
	inc->i_saddr = *saddr;
	inc->i_rdma_cookie = 0;
	inc->i_rx_tstamp.tv_sec = 0;
	inc->i_rx_tstamp.tv_usec = 0;

	for (i = 0; i < RDS_RX_MAX_TRACES; i++)
		inc->i_rx_lat_trace[i] = 0;
}