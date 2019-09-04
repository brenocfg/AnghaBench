#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  megacmd_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_3__ adapter_t ;
struct TYPE_7__ {TYPE_1__* host; } ;
struct TYPE_6__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_RESET ; 
 int /*<<< orphan*/  mega_rundoneq (TYPE_3__*) ; 
 int megaraid_abort_and_reset (TYPE_3__*,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
megaraid_reset(struct scsi_cmnd *cmd)
{
	adapter_t	*adapter;
	megacmd_t	mc;
	int		rval;

	adapter = (adapter_t *)cmd->device->host->hostdata;

#if MEGA_HAVE_CLUSTERING
	mc.cmd = MEGA_CLUSTER_CMD;
	mc.opcode = MEGA_RESET_RESERVATIONS;

	if( mega_internal_command(adapter, &mc, NULL) != 0 ) {
		dev_warn(&adapter->dev->dev, "reservation reset failed\n");
	}
	else {
		dev_info(&adapter->dev->dev, "reservation reset\n");
	}
#endif

	spin_lock_irq(&adapter->lock);

	rval =  megaraid_abort_and_reset(adapter, cmd, SCB_RESET);

	/*
	 * This is required here to complete any completed requests
	 * to be communicated over to the mid layer.
	 */
	mega_rundoneq(adapter);
	spin_unlock_irq(&adapter->lock);

	return rval;
}