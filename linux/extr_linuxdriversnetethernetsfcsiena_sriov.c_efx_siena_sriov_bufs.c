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
typedef  int u64 ;
struct efx_nic {scalar_t__ membase; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_QWORD_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRF_AZ_BUF_ADR_FBUF ; 
 int /*<<< orphan*/  FRF_AZ_BUF_ADR_REGION ; 
 int /*<<< orphan*/  FRF_AZ_BUF_OWNER_ID_FBUF ; 
 scalar_t__ FR_BZ_BUF_FULL_TBL ; 
 int /*<<< orphan*/  efx_sram_writeq (struct efx_nic*,scalar_t__,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void efx_siena_sriov_bufs(struct efx_nic *efx, unsigned offset,
				 u64 *addr, unsigned count)
{
	efx_qword_t buf;
	unsigned pos;

	for (pos = 0; pos < count; ++pos) {
		EFX_POPULATE_QWORD_3(buf,
				     FRF_AZ_BUF_ADR_REGION, 0,
				     FRF_AZ_BUF_ADR_FBUF,
				     addr ? addr[pos] >> 12 : 0,
				     FRF_AZ_BUF_OWNER_ID_FBUF, 0);
		efx_sram_writeq(efx, efx->membase + FR_BZ_BUF_FULL_TBL,
				&buf, offset + pos);
	}
}