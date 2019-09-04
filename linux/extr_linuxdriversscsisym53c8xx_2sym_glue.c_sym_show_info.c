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
struct seq_file {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int sym_show_info(struct seq_file *m, struct Scsi_Host *shost)
{
#ifdef SYM_LINUX_USER_INFO_SUPPORT
	struct sym_data *sym_data = shost_priv(shost);
	struct pci_dev *pdev = sym_data->pdev;
	struct sym_hcb *np = sym_data->ncb;

	seq_printf(m, "Chip " NAME53C "%s, device id 0x%x, "
		 "revision id 0x%x\n", np->s.chip_name,
		 pdev->device, pdev->revision);
	seq_printf(m, "At PCI address %s, IRQ %u\n",
			 pci_name(pdev), pdev->irq);
	seq_printf(m, "Min. period factor %d, %s SCSI BUS%s\n",
		 (int) (np->minsync_dt ? np->minsync_dt : np->minsync),
		 np->maxwide ? "Wide" : "Narrow",
		 np->minsync_dt ? ", DT capable" : "");

	seq_printf(m, "Max. started commands %d, "
		 "max. commands per LUN %d\n",
		 SYM_CONF_MAX_START, SYM_CONF_MAX_TAG);

	return 0;
#else
	return -EINVAL;
#endif /* SYM_LINUX_USER_INFO_SUPPORT */
}