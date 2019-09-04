#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {int /*<<< orphan*/  filter_sem; TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reconfigure_mac ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void efx_mac_reconfigure(struct efx_nic *efx)
{
	down_read(&efx->filter_sem);
	efx->type->reconfigure_mac(efx);
	up_read(&efx->filter_sem);
}