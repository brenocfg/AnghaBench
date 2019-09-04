#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct MPT3SAS_ADAPTER {scalar_t__ pending_io_count; int /*<<< orphan*/  reset_wq; int /*<<< orphan*/  shost; } ;

/* Variables and functions */
 int HZ ; 
 int MPI2_IOC_STATE_MASK ; 
 int MPI2_IOC_STATE_OPERATIONAL ; 
 int mpt3sas_base_get_iocstate (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_host_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

void
mpt3sas_wait_for_commands_to_complete(struct MPT3SAS_ADAPTER *ioc)
{
	u32 ioc_state;

	ioc->pending_io_count = 0;

	ioc_state = mpt3sas_base_get_iocstate(ioc, 0);
	if ((ioc_state & MPI2_IOC_STATE_MASK) != MPI2_IOC_STATE_OPERATIONAL)
		return;

	/* pending command count */
	ioc->pending_io_count = scsi_host_busy(ioc->shost);

	if (!ioc->pending_io_count)
		return;

	/* wait for pending commands to complete */
	wait_event_timeout(ioc->reset_wq, ioc->pending_io_count == 0, 10 * HZ);
}