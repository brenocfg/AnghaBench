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
struct rds_connection {TYPE_1__* c_trans; } ;
struct TYPE_2__ {scalar_t__ (* t_unloading ) (struct rds_connection*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  check_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_conn_net (struct rds_connection*) ; 
 scalar_t__ stub1 (struct rds_connection*) ; 

__attribute__((used)) static inline bool rds_destroy_pending(struct rds_connection *conn)
{
	return !check_net(rds_conn_net(conn)) ||
	       (conn->c_trans->t_unloading && conn->c_trans->t_unloading(conn));
}