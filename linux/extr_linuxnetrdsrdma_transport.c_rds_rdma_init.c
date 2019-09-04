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

/* Variables and functions */
 int /*<<< orphan*/  rds_ib_exit () ; 
 int rds_ib_init () ; 
 int rds_rdma_listen_init () ; 

__attribute__((used)) static int rds_rdma_init(void)
{
	int ret;

	ret = rds_ib_init();
	if (ret)
		goto out;

	ret = rds_rdma_listen_init();
	if (ret)
		rds_ib_exit();
out:
	return ret;
}