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
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_farch_interrupts (struct efx_nic*,int,int) ; 

void efx_farch_irq_disable_master(struct efx_nic *efx)
{
	/* Disable interrupts */
	efx_farch_interrupts(efx, false, false);
}