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
struct ef4_nic {int dummy; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ EF4_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRF_AB_EE_SPI_HCMD_CMD_EN ; 
 int /*<<< orphan*/  FR_AB_EE_SPI_HCMD ; 
 int /*<<< orphan*/  ef4_reado (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int falcon_spi_poll(struct ef4_nic *efx)
{
	ef4_oword_t reg;
	ef4_reado(efx, &reg, FR_AB_EE_SPI_HCMD);
	return EF4_OWORD_FIELD(reg, FRF_AB_EE_SPI_HCMD_CMD_EN) ? -EBUSY : 0;
}