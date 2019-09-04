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
 int ENOMEM ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  vfdi_workqueue ; 

int efx_init_sriov(void)
{
	/* A single threaded workqueue is sufficient. efx_siena_sriov_vfdi() and
	 * efx_siena_sriov_peer_work() spend almost all their time sleeping for
	 * MCDI to complete anyway
	 */
	vfdi_workqueue = create_singlethread_workqueue("sfc_vfdi");
	if (!vfdi_workqueue)
		return -ENOMEM;
	return 0;
}