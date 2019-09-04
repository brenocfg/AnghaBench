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
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct sym_hcb {TYPE_1__ s; } ;
struct pci_dev {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INB (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRST ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nc_istat ; 
 int /*<<< orphan*/  nc_mbox1 ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sym_free_resources (struct sym_hcb*,struct pci_dev*,int) ; 
 struct sym_hcb* sym_get_hcb (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sym_name (struct sym_hcb*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sym_detach(struct Scsi_Host *shost, struct pci_dev *pdev)
{
	struct sym_hcb *np = sym_get_hcb(shost);
	printk("%s: detaching ...\n", sym_name(np));

	del_timer_sync(&np->s.timer);

	/*
	 * Reset NCR chip.
	 * We should use sym_soft_reset(), but we don't want to do 
	 * so, since we may not be safe if interrupts occur.
	 */
	printk("%s: resetting chip\n", sym_name(np));
	OUTB(np, nc_istat, SRST);
	INB(np, nc_mbox1);
	udelay(10);
	OUTB(np, nc_istat, 0);

	sym_free_resources(np, pdev, 1);
	scsi_host_put(shost);

	return 1;
}