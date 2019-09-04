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
struct scsi_cmnd {TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  adapter_t ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_ABORT ; 
 int /*<<< orphan*/  mega_rundoneq (int /*<<< orphan*/ *) ; 
 int megaraid_abort_and_reset (int /*<<< orphan*/ *,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
megaraid_abort(struct scsi_cmnd *cmd)
{
	adapter_t	*adapter;
	int		rval;

	adapter = (adapter_t *)cmd->device->host->hostdata;

	rval =  megaraid_abort_and_reset(adapter, cmd, SCB_ABORT);

	/*
	 * This is required here to complete any completed requests
	 * to be communicated over to the mid layer.
	 */
	mega_rundoneq(adapter);

	return rval;
}