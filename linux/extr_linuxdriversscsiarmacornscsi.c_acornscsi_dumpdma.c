#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  scsi_xferred; int /*<<< orphan*/  this_residual; int /*<<< orphan*/  ptr; } ;
struct TYPE_12__ {TYPE_3__ SCp; } ;
struct TYPE_10__ {int /*<<< orphan*/  transferred; int /*<<< orphan*/  start_addr; } ;
struct TYPE_13__ {TYPE_4__ scsi; TYPE_2__ dma; TYPE_1__* host; } ;
struct TYPE_9__ {int /*<<< orphan*/  host_no; } ;
typedef  TYPE_5__ AS_Host ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_MASKREG ; 
 int /*<<< orphan*/  DMAC_MODECON ; 
 int /*<<< orphan*/  DMAC_TXCNTHI ; 
 int /*<<< orphan*/  DMAC_TXCNTLO ; 
 unsigned int dmac_address (TYPE_5__*) ; 
 int dmac_read (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static
void acornscsi_dumpdma(AS_Host *host, char *where)
{
	unsigned int mode, addr, len;

	mode = dmac_read(host, DMAC_MODECON);
	addr = dmac_address(host);
	len  = dmac_read(host, DMAC_TXCNTHI) << 8 |
	       dmac_read(host, DMAC_TXCNTLO);

	printk("scsi%d: %s: DMAC %02x @%06x+%04x msk %02x, ",
		host->host->host_no, where,
		mode, addr, (len + 1) & 0xffff,
		dmac_read(host, DMAC_MASKREG));

	printk("DMA @%06x, ", host->dma.start_addr);
	printk("BH @%p +%04x, ", host->scsi.SCp.ptr,
		host->scsi.SCp.this_residual);
	printk("DT @+%04x ST @+%04x", host->dma.transferred,
		host->scsi.SCp.scsi_xferred);
	printk("\n");
}