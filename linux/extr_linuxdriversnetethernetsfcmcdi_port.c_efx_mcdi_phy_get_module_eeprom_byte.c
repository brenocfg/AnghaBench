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
typedef  int u8 ;
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int efx_mcdi_phy_get_module_eeprom_page (struct efx_nic*,unsigned int,int*,int,int) ; 

__attribute__((used)) static int efx_mcdi_phy_get_module_eeprom_byte(struct efx_nic *efx,
					       unsigned int page,
					       u8 byte)
{
	int rc;
	u8 data;

	rc = efx_mcdi_phy_get_module_eeprom_page(efx, page, &data, byte, 1);
	if (rc == 1)
		return data;

	return rc;
}