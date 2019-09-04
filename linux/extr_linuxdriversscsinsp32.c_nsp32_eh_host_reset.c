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
struct scsi_cmnd {TYPE_1__* device; } ;
struct Scsi_Host {unsigned int io_port; int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  nsp32_hw_data ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_CONTROL ; 
 int /*<<< orphan*/  IRQ_CONTROL_ALL_IRQ_MASK ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  NSP32_DEBUG_BUSRESET ; 
 int SUCCESS ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  nsp32_do_bus_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nsp32_write2 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32hw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsp32_eh_host_reset(struct scsi_cmnd *SCpnt)
{
	struct Scsi_Host *host = SCpnt->device->host;
	unsigned int      base = SCpnt->device->host->io_port;
	nsp32_hw_data    *data = (nsp32_hw_data *)host->hostdata;

	nsp32_msg(KERN_INFO, "Host Reset");	
	nsp32_dbg(NSP32_DEBUG_BUSRESET, "SCpnt=0x%x", SCpnt);

	spin_lock_irq(SCpnt->device->host->host_lock);

	nsp32hw_init(data);
	nsp32_write2(base, IRQ_CONTROL, IRQ_CONTROL_ALL_IRQ_MASK);
	nsp32_do_bus_reset(data);
	nsp32_write2(base, IRQ_CONTROL, 0);

	spin_unlock_irq(SCpnt->device->host->host_lock);
	return SUCCESS;	/* Host reset is succeeded at any time. */
}