#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {char type; int id; int /*<<< orphan*/  vendor; } ;
struct TYPE_3__ {int bug_fix_cntl; int init_sdtr; int pci_fix_asyn_xfer_always; int pci_fix_asyn_xfer; int /*<<< orphan*/  iop_base; } ;
typedef  int ASC_SCSI_BIT_ID_TYPE ;
typedef  TYPE_1__ ASC_DVC_VAR ;

/* Variables and functions */
 int ASC_BUG_FIX_ASYN_USE_SYN ; 
 int /*<<< orphan*/  ASYN_SDTR_DATA_FIX_PCI_REV_AB ; 
 int /*<<< orphan*/  AscSetRunChipSynRegAtID (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char TYPE_PROCESSOR ; 
 char TYPE_ROM ; 
 char TYPE_SCANNER ; 
 char TYPE_TAPE ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void AscAsyncFix(ASC_DVC_VAR *asc_dvc, struct scsi_device *sdev)
{
	char type = sdev->type;
	ASC_SCSI_BIT_ID_TYPE tid_bits = 1 << sdev->id;

	if (!(asc_dvc->bug_fix_cntl & ASC_BUG_FIX_ASYN_USE_SYN))
		return;
	if (asc_dvc->init_sdtr & tid_bits)
		return;

	if ((type == TYPE_ROM) && (strncmp(sdev->vendor, "HP ", 3) == 0))
		asc_dvc->pci_fix_asyn_xfer_always |= tid_bits;

	asc_dvc->pci_fix_asyn_xfer |= tid_bits;
	if ((type == TYPE_PROCESSOR) || (type == TYPE_SCANNER) ||
	    (type == TYPE_ROM) || (type == TYPE_TAPE))
		asc_dvc->pci_fix_asyn_xfer &= ~tid_bits;

	if (asc_dvc->pci_fix_asyn_xfer & tid_bits)
		AscSetRunChipSynRegAtID(asc_dvc->iop_base, sdev->id,
					ASYN_SDTR_DATA_FIX_PCI_REV_AB);
}