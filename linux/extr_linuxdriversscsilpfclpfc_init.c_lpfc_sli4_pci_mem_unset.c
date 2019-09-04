#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  conf_regs_memmap_p; int /*<<< orphan*/  drbl_regs_memmap_p; int /*<<< orphan*/  ctrl_regs_memmap_p; int /*<<< orphan*/  sli_intf; } ;
struct lpfc_hba {TYPE_1__* pcidev; TYPE_2__ sli4_hba; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
#define  LPFC_SLI_INTF_IF_TYPE_0 131 
#define  LPFC_SLI_INTF_IF_TYPE_1 130 
#define  LPFC_SLI_INTF_IF_TYPE_2 129 
#define  LPFC_SLI_INTF_IF_TYPE_6 128 
 int bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 

__attribute__((used)) static void
lpfc_sli4_pci_mem_unset(struct lpfc_hba *phba)
{
	uint32_t if_type;
	if_type = bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf);

	switch (if_type) {
	case LPFC_SLI_INTF_IF_TYPE_0:
		iounmap(phba->sli4_hba.drbl_regs_memmap_p);
		iounmap(phba->sli4_hba.ctrl_regs_memmap_p);
		iounmap(phba->sli4_hba.conf_regs_memmap_p);
		break;
	case LPFC_SLI_INTF_IF_TYPE_2:
		iounmap(phba->sli4_hba.conf_regs_memmap_p);
		break;
	case LPFC_SLI_INTF_IF_TYPE_6:
		iounmap(phba->sli4_hba.drbl_regs_memmap_p);
		iounmap(phba->sli4_hba.conf_regs_memmap_p);
		break;
	case LPFC_SLI_INTF_IF_TYPE_1:
	default:
		dev_printk(KERN_ERR, &phba->pcidev->dev,
			   "FATAL - unsupported SLI4 interface type - %d\n",
			   if_type);
		break;
	}
}