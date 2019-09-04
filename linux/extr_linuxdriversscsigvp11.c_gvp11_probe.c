#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * SCMD; int /*<<< orphan*/ * SASR; } ;
typedef  TYPE_3__ wd33c93_regs ;
struct zorro_device_id {unsigned int driver_data; } ;
struct TYPE_5__ {unsigned long start; } ;
struct zorro_dev {int /*<<< orphan*/  slotaddr; TYPE_1__ resource; } ;
struct gvp11_scsiregs {int secret2; int secret3; int CNTR; int /*<<< orphan*/  SCMD; int /*<<< orphan*/  SASR; scalar_t__ BANK; scalar_t__ secret1; } ;
struct TYPE_6__ {unsigned int dma_xfer_mask; int no_sync; int /*<<< orphan*/  dma_mode; scalar_t__ fast; } ;
struct gvp11_hostdata {struct gvp11_scsiregs* regs; TYPE_2__ wh; } ;
struct Scsi_Host {int /*<<< orphan*/  unique_id; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_DMA ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int GVP11_DMAC_BUSY ; 
 int GVP11_DMAC_INT_ENABLE ; 
 unsigned int GVP_SCSICLKMASK ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_AMIGA_PORTS ; 
 int /*<<< orphan*/  WD33C93_FS_12_15 ; 
 int /*<<< orphan*/  WD33C93_FS_8_10 ; 
 struct gvp11_scsiregs* ZTWO_VADDR (unsigned long) ; 
 int check_wd33c93 (struct gvp11_scsiregs*) ; 
 int /*<<< orphan*/  dma_setup ; 
 int /*<<< orphan*/  dma_stop ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 int /*<<< orphan*/  gvp11_intr ; 
 int /*<<< orphan*/  gvp11_scsi_template ; 
 unsigned int gvp11_xfer_mask ; 
 int /*<<< orphan*/  release_mem_region (unsigned long,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct Scsi_Host*) ; 
 int /*<<< orphan*/  request_mem_region (unsigned long,int,char*) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 struct gvp11_hostdata* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  wd33c93_init (struct Scsi_Host*,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zorro_resource_len (struct zorro_dev*) ; 
 int /*<<< orphan*/  zorro_set_drvdata (struct zorro_dev*,struct Scsi_Host*) ; 

__attribute__((used)) static int gvp11_probe(struct zorro_dev *z, const struct zorro_device_id *ent)
{
	struct Scsi_Host *instance;
	unsigned long address;
	int error;
	unsigned int epc;
	unsigned int default_dma_xfer_mask;
	struct gvp11_hostdata *hdata;
	struct gvp11_scsiregs *regs;
	wd33c93_regs wdregs;

	default_dma_xfer_mask = ent->driver_data;

	/*
	 * Rumors state that some GVP ram boards use the same product
	 * code as the SCSI controllers. Therefore if the board-size
	 * is not 64KB we assume it is a ram board and bail out.
	 */
	if (zorro_resource_len(z) != 0x10000)
		return -ENODEV;

	address = z->resource.start;
	if (!request_mem_region(address, 256, "wd33c93"))
		return -EBUSY;

	regs = ZTWO_VADDR(address);

	error = check_wd33c93(regs);
	if (error)
		goto fail_check_or_alloc;

	instance = scsi_host_alloc(&gvp11_scsi_template,
				   sizeof(struct gvp11_hostdata));
	if (!instance) {
		error = -ENOMEM;
		goto fail_check_or_alloc;
	}

	instance->irq = IRQ_AMIGA_PORTS;
	instance->unique_id = z->slotaddr;

	regs->secret2 = 1;
	regs->secret1 = 0;
	regs->secret3 = 15;
	while (regs->CNTR & GVP11_DMAC_BUSY)
		;
	regs->CNTR = 0;
	regs->BANK = 0;

	wdregs.SASR = &regs->SASR;
	wdregs.SCMD = &regs->SCMD;

	hdata = shost_priv(instance);
	if (gvp11_xfer_mask)
		hdata->wh.dma_xfer_mask = gvp11_xfer_mask;
	else
		hdata->wh.dma_xfer_mask = default_dma_xfer_mask;

	hdata->wh.no_sync = 0xff;
	hdata->wh.fast = 0;
	hdata->wh.dma_mode = CTRL_DMA;
	hdata->regs = regs;

	/*
	 * Check for 14MHz SCSI clock
	 */
	epc = *(unsigned short *)(ZTWO_VADDR(address) + 0x8000);
	wd33c93_init(instance, wdregs, dma_setup, dma_stop,
		     (epc & GVP_SCSICLKMASK) ? WD33C93_FS_8_10
					     : WD33C93_FS_12_15);

	error = request_irq(IRQ_AMIGA_PORTS, gvp11_intr, IRQF_SHARED,
			    "GVP11 SCSI", instance);
	if (error)
		goto fail_irq;

	regs->CNTR = GVP11_DMAC_INT_ENABLE;

	error = scsi_add_host(instance, NULL);
	if (error)
		goto fail_host;

	zorro_set_drvdata(z, instance);
	scsi_scan_host(instance);
	return 0;

fail_host:
	free_irq(IRQ_AMIGA_PORTS, instance);
fail_irq:
	scsi_host_put(instance);
fail_check_or_alloc:
	release_mem_region(address, 256);
	return error;
}