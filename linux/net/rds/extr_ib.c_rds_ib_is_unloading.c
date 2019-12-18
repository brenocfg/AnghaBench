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
struct rds_connection {struct rds_conn_path* c_path; } ;
struct rds_conn_path {int /*<<< orphan*/  cp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_DESTROY_PENDING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_unloading ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rds_ib_is_unloading(struct rds_connection *conn)
{
	struct rds_conn_path *cp = &conn->c_path[0];

	return (test_bit(RDS_DESTROY_PENDING, &cp->cp_flags) ||
		atomic_read(&rds_ib_unloading) != 0);
}