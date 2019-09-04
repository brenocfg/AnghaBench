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
typedef  int /*<<< orphan*/  u32 ;
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ER_DZ_MC_DB_LWRD ; 
 int /*<<< orphan*/  _efx_writed (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_ef10_ptp_write_host_time(struct efx_nic *efx, u32 host_time)
{
	_efx_writed(efx, cpu_to_le32(host_time), ER_DZ_MC_DB_LWRD);
}