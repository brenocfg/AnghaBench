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
struct TYPE_2__ {int /*<<< orphan*/  rx_tstamp; scalar_t__ rdma_cookie; } ;
struct in6_addr {int dummy; } ;
struct rds_incoming {TYPE_1__ i_usercopy; struct in6_addr i_saddr; struct rds_conn_path* i_conn_path; int /*<<< orphan*/  i_conn; int /*<<< orphan*/  i_item; int /*<<< orphan*/  i_refcount; } ;
struct rds_conn_path {int /*<<< orphan*/  cp_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

void rds_inc_path_init(struct rds_incoming *inc, struct rds_conn_path *cp,
		       struct in6_addr  *saddr)
{
	refcount_set(&inc->i_refcount, 1);
	INIT_LIST_HEAD(&inc->i_item);
	inc->i_conn = cp->cp_conn;
	inc->i_conn_path = cp;
	inc->i_saddr = *saddr;
	inc->i_usercopy.rdma_cookie = 0;
	inc->i_usercopy.rx_tstamp = ktime_set(0, 0);
}