#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ scb_addr; } ;
typedef  TYPE_3__ ips_stat_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* callback ) (TYPE_5__*,TYPE_4__*) ;} ;
typedef  TYPE_4__ ips_scb_t ;
struct TYPE_15__ {int (* isintr ) (TYPE_5__*) ;int (* statupd ) (TYPE_5__*) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  pcidev; TYPE_1__ func; TYPE_3__ sp; int /*<<< orphan*/  active; } ;
typedef  TYPE_5__ ips_ha_t ;
struct TYPE_16__ {int command_id; } ;
struct TYPE_20__ {int value; TYPE_2__ fields; } ;
typedef  TYPE_6__ IPS_STATUS ;

/* Variables and functions */
 int IPS_MAX_CMDS ; 
 int /*<<< orphan*/  IPS_PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ips_chkstatus (TYPE_5__*,TYPE_6__*) ; 
 int stub1 (TYPE_5__*) ; 
 int stub2 (TYPE_5__*) ; 
 int stub3 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_5__*,TYPE_4__*) ; 

int
ips_intr_morpheus(ips_ha_t * ha)
{
	ips_stat_t *sp;
	ips_scb_t *scb;
	IPS_STATUS cstatus;
	int intrstatus;

	METHOD_TRACE("ips_intr_morpheus", 2);

	if (!ha)
		return 0;

	if (!ha->active)
		return 0;

	intrstatus = (*ha->func.isintr) (ha);

	if (!intrstatus) {
		/*
		 * Unexpected/Shared interrupt
		 */

		return 0;
	}

	while (TRUE) {
		sp = &ha->sp;

		intrstatus = (*ha->func.isintr) (ha);

		if (!intrstatus)
			break;
		else
			cstatus.value = (*ha->func.statupd) (ha);

		if (cstatus.value == 0xffffffff)
			/* No more to process */
			break;

		if (cstatus.fields.command_id > (IPS_MAX_CMDS - 1)) {
			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "Spurious interrupt; no ccb.\n");

			continue;
		}

		ips_chkstatus(ha, &cstatus);
		scb = (ips_scb_t *) sp->scb_addr;

		/*
		 * use the callback function to finish things up
		 * NOTE: interrupts are OFF for this
		 */
		(*scb->callback) (ha, scb);
	}			/* end while */
	return 1;
}