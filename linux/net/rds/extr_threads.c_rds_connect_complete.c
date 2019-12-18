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
struct rds_connection {int /*<<< orphan*/ * c_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_CONN_CONNECTING ; 
 int /*<<< orphan*/  rds_connect_path_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rds_connect_complete(struct rds_connection *conn)
{
	rds_connect_path_complete(&conn->c_path[0], RDS_CONN_CONNECTING);
}