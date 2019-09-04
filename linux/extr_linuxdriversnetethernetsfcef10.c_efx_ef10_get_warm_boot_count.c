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
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int EFX_DWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_WORD_0 ; 
 int /*<<< orphan*/  EFX_WORD_1 ; 
 int EIO ; 
 int /*<<< orphan*/  ER_DZ_BIU_MC_SFT_STATUS ; 
 int /*<<< orphan*/  efx_readd (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_ef10_get_warm_boot_count(struct efx_nic *efx)
{
	efx_dword_t reg;

	efx_readd(efx, &reg, ER_DZ_BIU_MC_SFT_STATUS);
	return EFX_DWORD_FIELD(reg, EFX_WORD_1) == 0xb007 ?
		EFX_DWORD_FIELD(reg, EFX_WORD_0) : -EIO;
}