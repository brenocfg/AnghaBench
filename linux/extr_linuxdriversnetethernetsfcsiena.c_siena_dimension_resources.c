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
 int FR_CZ_BUF_FULL_TBL_ROWS ; 
 int /*<<< orphan*/  efx_farch_dimension_resources (struct efx_nic*,int) ; 

__attribute__((used)) static int siena_dimension_resources(struct efx_nic *efx)
{
	/* Each port has a small block of internal SRAM dedicated to
	 * the buffer table and descriptor caches.  In theory we can
	 * map both blocks to one port, but we don't.
	 */
	efx_farch_dimension_resources(efx, FR_CZ_BUF_FULL_TBL_ROWS / 2);
	return 0;
}