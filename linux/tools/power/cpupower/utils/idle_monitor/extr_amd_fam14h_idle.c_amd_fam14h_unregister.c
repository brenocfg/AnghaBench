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
 int AMD_FAM14H_STATE_NUM ; 
 int /*<<< orphan*/ * current_count ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_acc ; 
 int /*<<< orphan*/  pci_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * previous_count ; 

__attribute__((used)) static void amd_fam14h_unregister(void)
{
	int num;
	for (num = 0; num < AMD_FAM14H_STATE_NUM - 1; num++) {
		free(previous_count[num]);
		free(current_count[num]);
	}
	pci_cleanup(pci_acc);
}