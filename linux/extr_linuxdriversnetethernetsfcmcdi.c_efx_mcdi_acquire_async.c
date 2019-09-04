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
struct efx_mcdi_iface {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ MCDI_STATE_QUIESCENT ; 
 int /*<<< orphan*/  MCDI_STATE_RUNNING_ASYNC ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool efx_mcdi_acquire_async(struct efx_mcdi_iface *mcdi)
{
	return cmpxchg(&mcdi->state,
		       MCDI_STATE_QUIESCENT, MCDI_STATE_RUNNING_ASYNC) ==
		MCDI_STATE_QUIESCENT;
}