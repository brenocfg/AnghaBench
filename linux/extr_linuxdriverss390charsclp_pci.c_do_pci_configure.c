#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int response_code; int /*<<< orphan*/  length; } ;
struct pci_cfg_sccb {TYPE_1__ header; int /*<<< orphan*/  aid; int /*<<< orphan*/  atype; } ;
typedef  int /*<<< orphan*/  sclp_cmdw_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SCLP_ATYPE_PCI ; 
 int /*<<< orphan*/  SCLP_HAS_PCI_RECONFIG ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int sclp_sync_request (int /*<<< orphan*/ ,struct pci_cfg_sccb*) ; 

__attribute__((used)) static int do_pci_configure(sclp_cmdw_t cmd, u32 fid)
{
	struct pci_cfg_sccb *sccb;
	int rc;

	if (!SCLP_HAS_PCI_RECONFIG)
		return -EOPNOTSUPP;

	sccb = (struct pci_cfg_sccb *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	if (!sccb)
		return -ENOMEM;

	sccb->header.length = PAGE_SIZE;
	sccb->atype = SCLP_ATYPE_PCI;
	sccb->aid = fid;
	rc = sclp_sync_request(cmd, sccb);
	if (rc)
		goto out;
	switch (sccb->header.response_code) {
	case 0x0020:
	case 0x0120:
		break;
	default:
		pr_warn("configure PCI I/O adapter failed: cmd=0x%08x  response=0x%04x\n",
			cmd, sccb->header.response_code);
		rc = -EIO;
		break;
	}
out:
	free_page((unsigned long) sccb);
	return rc;
}