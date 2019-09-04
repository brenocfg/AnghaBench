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
struct mvumi_hba {int /*<<< orphan*/ * pci_base; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 unsigned char MAX_BASE_ADDRESS ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mvumi_backup_bar_addr(struct mvumi_hba *mhba)
{
	unsigned char i;

	for (i = 0; i < MAX_BASE_ADDRESS; i++) {
		pci_read_config_dword(mhba->pdev, 0x10 + i * 4,
						&mhba->pci_base[i]);
	}
}