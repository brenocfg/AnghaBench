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
 size_t EEPROM_MAC_ADDR_8723BS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 struct eeprom_priv* GET_EEPROM_EFUSE_PRIV (struct adapter*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Hal_EfuseParseMACAddr_8723BS(
	struct adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
{
	u16 i;
	u8 sMacAddr[6] = {0x00, 0xE0, 0x4C, 0xb7, 0x23, 0x00};
	struct eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	if (AutoLoadFail) {
/* 		sMacAddr[5] = (u8)GetRandomNumber(1, 254); */
		for (i = 0; i < 6; i++)
			pEEPROM->mac_addr[i] = sMacAddr[i];
	} else {
		/* Read Permanent MAC address */
		memcpy(pEEPROM->mac_addr, &hwinfo[EEPROM_MAC_ADDR_8723BS], ETH_ALEN);
	}
/* 	NicIFSetMacAddress(padapter, padapter->PermanentAddress); */

	RT_TRACE(
		_module_hci_hal_init_c_,
		_drv_notice_,
		(
			"Hal_EfuseParseMACAddr_8723BS: Permanent Address = %02x-%02x-%02x-%02x-%02x-%02x\n",
			pEEPROM->mac_addr[0],
			pEEPROM->mac_addr[1],
			pEEPROM->mac_addr[2],
			pEEPROM->mac_addr[3],
			pEEPROM->mac_addr[4],
			pEEPROM->mac_addr[5]
		)
	);
}