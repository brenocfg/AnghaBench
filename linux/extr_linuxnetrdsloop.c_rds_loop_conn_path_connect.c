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
struct rds_conn_path {int /*<<< orphan*/  cp_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  rds_connect_complete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rds_loop_conn_path_connect(struct rds_conn_path *cp)
{
	rds_connect_complete(cp->cp_conn);
	return 0;
}