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
struct TYPE_4__ {int /*<<< orphan*/  this_residual; int /*<<< orphan*/  ptr; } ;
struct scsi_cmnd {TYPE_2__ SCp; TYPE_1__* device; } ;
struct a3000_scsiregs {unsigned short CNTR; unsigned long ACR; int ST_DMA; } ;
struct WD33C93_hostdata {int dma_bounce_len; int dma_dir; int /*<<< orphan*/  dma_bounce_buffer; } ;
struct a3000_hostdata {struct a3000_scsiregs* regs; struct WD33C93_hostdata wh; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 unsigned long A3000_XFER_MASK ; 
 unsigned short CNTR_DDIR ; 
 unsigned short CNTR_INTEN ; 
 unsigned short CNTR_PDMD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cache_clear (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_push (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct a3000_hostdata* shost_priv (struct Scsi_Host*) ; 
 unsigned long virt_to_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dma_setup(struct scsi_cmnd *cmd, int dir_in)
{
	struct Scsi_Host *instance = cmd->device->host;
	struct a3000_hostdata *hdata = shost_priv(instance);
	struct WD33C93_hostdata *wh = &hdata->wh;
	struct a3000_scsiregs *regs = hdata->regs;
	unsigned short cntr = CNTR_PDMD | CNTR_INTEN;
	unsigned long addr = virt_to_bus(cmd->SCp.ptr);

	/*
	 * if the physical address has the wrong alignment, or if
	 * physical address is bad, or if it is a write and at the
	 * end of a physical memory chunk, then allocate a bounce
	 * buffer
	 */
	if (addr & A3000_XFER_MASK) {
		wh->dma_bounce_len = (cmd->SCp.this_residual + 511) & ~0x1ff;
		wh->dma_bounce_buffer = kmalloc(wh->dma_bounce_len,
						GFP_KERNEL);

		/* can't allocate memory; use PIO */
		if (!wh->dma_bounce_buffer) {
			wh->dma_bounce_len = 0;
			return 1;
		}

		if (!dir_in) {
			/* copy to bounce buffer for a write */
			memcpy(wh->dma_bounce_buffer, cmd->SCp.ptr,
			       cmd->SCp.this_residual);
		}

		addr = virt_to_bus(wh->dma_bounce_buffer);
	}

	/* setup dma direction */
	if (!dir_in)
		cntr |= CNTR_DDIR;

	/* remember direction */
	wh->dma_dir = dir_in;

	regs->CNTR = cntr;

	/* setup DMA *physical* address */
	regs->ACR = addr;

	if (dir_in) {
		/* invalidate any cache */
		cache_clear(addr, cmd->SCp.this_residual);
	} else {
		/* push any dirty cache */
		cache_push(addr, cmd->SCp.this_residual);
	}

	/* start DMA */
	mb();			/* make sure setup is completed */
	regs->ST_DMA = 1;
	mb();			/* make sure DMA has started before next IO */

	/* return success */
	return 0;
}