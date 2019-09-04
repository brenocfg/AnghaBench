#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ reserved4; scalar_t__ reserved3; scalar_t__ reserved2; scalar_t__ reserved; int /*<<< orphan*/  state; int /*<<< orphan*/  command_id; void* op_code; } ;
struct TYPE_17__ {TYPE_1__ flush_cache; } ;
struct TYPE_19__ {TYPE_2__ cmd; void** cdb; int /*<<< orphan*/  timeout; int /*<<< orphan*/  scb_busaddr; } ;
typedef  TYPE_4__ ips_scb_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* reset ) (TYPE_5__*) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  pcidev; TYPE_3__ func; } ;
typedef  TYPE_5__ ips_ha_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 void* IPS_CMD_FLUSH ; 
 int /*<<< orphan*/  IPS_MAX_CMDS ; 
 int /*<<< orphan*/  IPS_NORM_STATE ; 
 int IPS_ONE_SEC ; 
 int IPS_SUCCESS ; 
 int /*<<< orphan*/  ips_cmd_timeout ; 
 int /*<<< orphan*/  ips_init_scb (TYPE_5__*,TYPE_4__*) ; 
 int ips_poll_for_flush_complete (TYPE_5__*) ; 
 int ips_send_cmd (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
ips_flush_and_reset(ips_ha_t *ha)
{
	ips_scb_t *scb;
	int  ret;
 	int  time;
	int  done;
	dma_addr_t command_dma;

	/* Create a usuable SCB */
	scb = pci_alloc_consistent(ha->pcidev, sizeof(ips_scb_t), &command_dma);
	if (scb) {
	    memset(scb, 0, sizeof(ips_scb_t));
	    ips_init_scb(ha, scb);
	    scb->scb_busaddr = command_dma;

	    scb->timeout = ips_cmd_timeout;
	    scb->cdb[0] = IPS_CMD_FLUSH;

	    scb->cmd.flush_cache.op_code = IPS_CMD_FLUSH;
	    scb->cmd.flush_cache.command_id = IPS_MAX_CMDS;   /* Use an ID that would otherwise not exist */
	    scb->cmd.flush_cache.state = IPS_NORM_STATE;
	    scb->cmd.flush_cache.reserved = 0;
	    scb->cmd.flush_cache.reserved2 = 0;
	    scb->cmd.flush_cache.reserved3 = 0;
	    scb->cmd.flush_cache.reserved4 = 0;

	    ret = ips_send_cmd(ha, scb);                      /* Send the Flush Command */

	    if (ret == IPS_SUCCESS) {
	        time = 60 * IPS_ONE_SEC;	              /* Max Wait time is 60 seconds */
	        done = 0;

	        while ((time > 0) && (!done)) {
		   done = ips_poll_for_flush_complete(ha);
	           /* This may look evil, but it's only done during extremely rare start-up conditions ! */
	           udelay(1000);
	           time--;
	        }
        }
	}

	/* Now RESET and INIT the adapter */
	(*ha->func.reset) (ha);

	pci_free_consistent(ha->pcidev, sizeof(ips_scb_t), scb, command_dma);
	return;
}