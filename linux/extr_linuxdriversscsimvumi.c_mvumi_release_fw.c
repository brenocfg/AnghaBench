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
struct mvumi_hba {int /*<<< orphan*/  pdev; int /*<<< orphan*/  regs; int /*<<< orphan*/  handshake_page_phys; int /*<<< orphan*/  handshake_page; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSP_MAX_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvumi_free_cmds (struct mvumi_hba*) ; 
 int /*<<< orphan*/  mvumi_release_mem_resource (struct mvumi_hba*) ; 
 int /*<<< orphan*/  mvumi_unmap_pci_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvumi_release_fw(struct mvumi_hba *mhba)
{
	mvumi_free_cmds(mhba);
	mvumi_release_mem_resource(mhba);
	mvumi_unmap_pci_addr(mhba->pdev, mhba->base_addr);
	pci_free_consistent(mhba->pdev, HSP_MAX_SIZE,
		mhba->handshake_page, mhba->handshake_page_phys);
	kfree(mhba->regs);
	pci_release_regions(mhba->pdev);
}