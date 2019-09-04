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
struct ef4_nic {int /*<<< orphan*/  irq_level; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_POPULATE_OWORD_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_AZ_DRV_INT_EN_KER ; 
 int /*<<< orphan*/  FRF_AZ_KER_INT_KER ; 
 int /*<<< orphan*/  FRF_AZ_KER_INT_LEVE_SEL ; 
 int /*<<< orphan*/  FR_AZ_INT_EN_KER ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ef4_farch_interrupts(struct ef4_nic *efx,
				      bool enabled, bool force)
{
	ef4_oword_t int_en_reg_ker;

	EF4_POPULATE_OWORD_3(int_en_reg_ker,
			     FRF_AZ_KER_INT_LEVE_SEL, efx->irq_level,
			     FRF_AZ_KER_INT_KER, force,
			     FRF_AZ_DRV_INT_EN_KER, enabled);
	ef4_writeo(efx, &int_en_reg_ker, FR_AZ_INT_EN_KER);
}