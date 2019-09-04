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
struct efx_nic {int /*<<< orphan*/  active_queues; int /*<<< orphan*/  rxq_flush_outstanding; int /*<<< orphan*/  rxq_flush_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void efx_farch_finish_flr(struct efx_nic *efx)
{
	atomic_set(&efx->rxq_flush_pending, 0);
	atomic_set(&efx->rxq_flush_outstanding, 0);
	atomic_set(&efx->active_queues, 0);
}