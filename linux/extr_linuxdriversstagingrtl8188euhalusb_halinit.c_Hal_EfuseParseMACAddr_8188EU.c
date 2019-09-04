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
typedef  int u16 ;
struct eeprom_priv {int* mac_addr; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 size_t EEPROM_MAC_ADDR_88EU ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 struct eeprom_priv* GET_EEPROM_EFUSE_PRIV (struct adapter*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Hal_EfuseParseMACAddr_8188EU(struct adapter *adapt, u8 *hwinfo, bool AutoLoadFail)
{
	u16 i;
	u8 sMacAddr[6] = {0x00, 0xE0, 0x4C, 0x81, 0x88, 0x02};
	struct eeprom_priv *eeprom = GET_EEPROM_EFUSE_PRIV(adapt);

	if (AutoLoadFail) {
		for (i = 0; i < 6; i++)
			eeprom->mac_addr[i] = sMacAddr[i];
	} else {
		/* Read Permanent MAC address */
		memcpy(eeprom->mac_addr, &hwinfo[EEPROM_MAC_ADDR_88EU], ETH_ALEN);
	}
	RT_TRACE(_module_hci_hal_init_c_, _drv_notice_,
		 ("Hal_EfuseParseMACAddr_8188EU: Permanent Address = %pM\n",
		 eeprom->mac_addr));
}