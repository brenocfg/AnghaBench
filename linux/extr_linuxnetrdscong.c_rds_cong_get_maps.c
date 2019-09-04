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
struct rds_connection {void* c_fcong; void* c_lcong; int /*<<< orphan*/  c_faddr; int /*<<< orphan*/  c_laddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* rds_cong_from_addr (int /*<<< orphan*/ *) ; 

int rds_cong_get_maps(struct rds_connection *conn)
{
	conn->c_lcong = rds_cong_from_addr(&conn->c_laddr);
	conn->c_fcong = rds_cong_from_addr(&conn->c_faddr);

	if (!(conn->c_lcong && conn->c_fcong))
		return -ENOMEM;

	return 0;
}