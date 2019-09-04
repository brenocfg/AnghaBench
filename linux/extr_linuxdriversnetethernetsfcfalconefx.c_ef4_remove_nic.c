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
struct ef4_nic {TYPE_1__* type; int /*<<< orphan*/  net_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ef4_remove_interrupts (struct ef4_nic*) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 

__attribute__((used)) static void ef4_remove_nic(struct ef4_nic *efx)
{
	netif_dbg(efx, drv, efx->net_dev, "destroying NIC\n");

	ef4_remove_interrupts(efx);
	efx->type->remove(efx);
}