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
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_unregister_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_client ; 
 int /*<<< orphan*/  rds_wq ; 

__attribute__((used)) static void rds_ib_unregister_client(void)
{
	ib_unregister_client(&rds_ib_client);
	/* wait for rds_ib_dev_free() to complete */
	flush_workqueue(rds_wq);
}