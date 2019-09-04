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
struct iscsi_conn {int /*<<< orphan*/  conn_transport; struct iscsi_conn* conn_ops; int /*<<< orphan*/  conn_cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_put_transport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iscsi_conn*) ; 

void iscsit_free_conn(struct iscsi_conn *conn)
{
	free_cpumask_var(conn->conn_cpumask);
	kfree(conn->conn_ops);
	iscsit_put_transport(conn->conn_transport);
	kfree(conn);
}