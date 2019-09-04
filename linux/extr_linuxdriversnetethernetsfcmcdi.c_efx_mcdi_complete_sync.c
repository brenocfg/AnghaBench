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
struct efx_mcdi_iface {int /*<<< orphan*/  wq; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCDI_STATE_COMPLETED ; 
 scalar_t__ MCDI_STATE_RUNNING_SYNC ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool efx_mcdi_complete_sync(struct efx_mcdi_iface *mcdi)
{
	if (cmpxchg(&mcdi->state,
		    MCDI_STATE_RUNNING_SYNC, MCDI_STATE_COMPLETED) ==
	    MCDI_STATE_RUNNING_SYNC) {
		wake_up(&mcdi->wq);
		return true;
	}

	return false;
}