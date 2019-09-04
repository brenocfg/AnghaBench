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
struct pmcraid_instance {scalar_t__* host_toggle_bit; scalar_t__* hrrq_start_bus_addr; int /*<<< orphan*/ ** hrrq_start; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int HRRQ_ENTRY_SIZE ; 
 int PMCRAID_MAX_CMD ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
pmcraid_release_host_rrqs(struct pmcraid_instance *pinstance, int maxindex)
{
	int i;
	for (i = 0; i < maxindex; i++) {

		pci_free_consistent(pinstance->pdev,
				    HRRQ_ENTRY_SIZE * PMCRAID_MAX_CMD,
				    pinstance->hrrq_start[i],
				    pinstance->hrrq_start_bus_addr[i]);

		/* reset pointers and toggle bit to zeros */
		pinstance->hrrq_start[i] = NULL;
		pinstance->hrrq_start_bus_addr[i] = 0;
		pinstance->host_toggle_bit[i] = 0;
	}
}