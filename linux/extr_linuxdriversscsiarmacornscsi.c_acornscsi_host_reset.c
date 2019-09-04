#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_11__ {int /*<<< orphan*/  disconnected; } ;
struct TYPE_10__ {int resets; } ;
struct TYPE_12__ {TYPE_4__ queues; TYPE_3__ stats; } ;
struct TYPE_9__ {TYPE_1__* host; } ;
struct TYPE_8__ {scalar_t__ hostdata; } ;
typedef  TYPE_5__ AS_Host ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  acornscsi_dma_stop (TYPE_5__*) ; 
 int /*<<< orphan*/  acornscsi_resetcard (TYPE_5__*) ; 
 struct scsi_cmnd* queue_remove (int /*<<< orphan*/ *) ; 

int acornscsi_host_reset(struct scsi_cmnd *SCpnt)
{
	AS_Host *host = (AS_Host *)SCpnt->device->host->hostdata;
	struct scsi_cmnd *SCptr;
    
    host->stats.resets += 1;

#if (DEBUG & DEBUG_RESET)
    {
	int asr, ssr, devidx;

	asr = sbic_arm_read(host, SBIC_ASR);
	ssr = sbic_arm_read(host, SBIC_SSR);

	printk(KERN_WARNING "acornscsi_reset: ");
	print_sbic_status(asr, ssr, host->scsi.phase);
	for (devidx = 0; devidx < 9; devidx++)
	    acornscsi_dumplog(host, devidx);
    }
#endif

    acornscsi_dma_stop(host);

    /*
     * do hard reset.  This resets all devices on this host, and so we
     * must set the reset status on all commands.
     */
    acornscsi_resetcard(host);

    while ((SCptr = queue_remove(&host->queues.disconnected)) != NULL)
	;

    return SUCCESS;
}