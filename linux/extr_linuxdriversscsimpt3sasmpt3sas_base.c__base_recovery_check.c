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
struct MPT3SAS_ADAPTER {scalar_t__ pending_io_count; int /*<<< orphan*/  reset_wq; int /*<<< orphan*/  shost; scalar_t__ shost_recovery; } ;

/* Variables and functions */
 scalar_t__ scsi_host_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_base_recovery_check(struct MPT3SAS_ADAPTER *ioc)
{
	/*
	 * See _wait_for_commands_to_complete() call with regards to this code.
	 */
	if (ioc->shost_recovery && ioc->pending_io_count) {
		ioc->pending_io_count = scsi_host_busy(ioc->shost);
		if (ioc->pending_io_count == 0)
			wake_up(&ioc->reset_wq);
	}
}