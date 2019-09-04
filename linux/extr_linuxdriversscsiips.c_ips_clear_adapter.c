#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ reserved3; scalar_t__ reserved2; scalar_t__ reserved; int /*<<< orphan*/  control; scalar_t__ log_drv; void* command_id; void* op_code; } ;
struct TYPE_13__ {scalar_t__ reserved3; scalar_t__ reserved2; scalar_t__ reserved; int /*<<< orphan*/  source_target; scalar_t__ channel; void* command_id; void* op_code; } ;
struct TYPE_15__ {TYPE_2__ unlock_stripe; TYPE_1__ config_sync; } ;
struct TYPE_16__ {int basic_status; TYPE_3__ cmd; void* timeout; void** cdb; } ;
typedef  TYPE_4__ ips_scb_t ;
struct TYPE_17__ {int max_cmds; TYPE_4__* scbs; } ;
typedef  TYPE_5__ ips_ha_t ;

/* Variables and functions */
 void* IPS_CMD_CONFIG_SYNC ; 
 void* IPS_CMD_ERROR_TABLE ; 
 void* IPS_COMMAND_ID (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  IPS_CSL ; 
 int IPS_FAILURE ; 
 int IPS_GSC_STATUS_MASK ; 
 int /*<<< orphan*/  IPS_POCL ; 
 int IPS_SUCCESS_IMM ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 void* ips_cmd_timeout ; 
 int /*<<< orphan*/  ips_init_scb (TYPE_5__*,TYPE_4__*) ; 
 void* ips_reset_timeout ; 
 int ips_send_wait (TYPE_5__*,TYPE_4__*,void*,int) ; 

__attribute__((used)) static int
ips_clear_adapter(ips_ha_t * ha, int intr)
{
	ips_scb_t *scb;
	int ret;

	METHOD_TRACE("ips_clear_adapter", 1);

	scb = &ha->scbs[ha->max_cmds - 1];

	ips_init_scb(ha, scb);

	scb->timeout = ips_reset_timeout;
	scb->cdb[0] = IPS_CMD_CONFIG_SYNC;

	scb->cmd.config_sync.op_code = IPS_CMD_CONFIG_SYNC;
	scb->cmd.config_sync.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.config_sync.channel = 0;
	scb->cmd.config_sync.source_target = IPS_POCL;
	scb->cmd.config_sync.reserved = 0;
	scb->cmd.config_sync.reserved2 = 0;
	scb->cmd.config_sync.reserved3 = 0;

	/* issue command */
	if (((ret =
	      ips_send_wait(ha, scb, ips_reset_timeout, intr)) == IPS_FAILURE)
	    || (ret == IPS_SUCCESS_IMM)
	    || ((scb->basic_status & IPS_GSC_STATUS_MASK) > 1))
		return (0);

	/* send unlock stripe command */
	ips_init_scb(ha, scb);

	scb->cdb[0] = IPS_CMD_ERROR_TABLE;
	scb->timeout = ips_reset_timeout;

	scb->cmd.unlock_stripe.op_code = IPS_CMD_ERROR_TABLE;
	scb->cmd.unlock_stripe.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.unlock_stripe.log_drv = 0;
	scb->cmd.unlock_stripe.control = IPS_CSL;
	scb->cmd.unlock_stripe.reserved = 0;
	scb->cmd.unlock_stripe.reserved2 = 0;
	scb->cmd.unlock_stripe.reserved3 = 0;

	/* issue command */
	if (((ret =
	      ips_send_wait(ha, scb, ips_cmd_timeout, intr)) == IPS_FAILURE)
	    || (ret == IPS_SUCCESS_IMM)
	    || ((scb->basic_status & IPS_GSC_STATUS_MASK) > 1))
		return (0);

	return (1);
}