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
struct rds_connection {int /*<<< orphan*/ * c_path; TYPE_1__* c_trans; } ;
struct TYPE_2__ {int /*<<< orphan*/  t_mp_capable; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int rds_conn_path_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
rds_conn_state(struct rds_connection *conn)
{
	WARN_ON(conn->c_trans->t_mp_capable);
	return rds_conn_path_state(&conn->c_path[0]);
}