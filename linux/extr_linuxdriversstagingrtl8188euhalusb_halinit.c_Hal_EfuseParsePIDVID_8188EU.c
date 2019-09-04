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
typedef  void* u8 ;
struct hal_data_8188e {void* EEPROMSubCustomerID; void* EEPROMCustomerID; void* EEPROMPID; void* EEPROMVID; } ;
struct adapter {struct hal_data_8188e* HalData; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,void*,void*) ; 
 size_t EEPROM_CUSTOMERID_88E ; 
 void* EEPROM_Default_CustomerID ; 
 void* EEPROM_Default_PID ; 
 void* EEPROM_Default_SubCustomerID ; 
 void* EEPROM_Default_VID ; 
 size_t EEPROM_PID_88EU ; 
 size_t EEPROM_VID_88EU ; 
 void* EF2BYTE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Hal_EfuseParsePIDVID_8188EU(struct adapter *adapt, u8 *hwinfo, bool AutoLoadFail)
{
	struct hal_data_8188e *haldata = adapt->HalData;

	if (!AutoLoadFail) {
		/*  VID, PID */
		haldata->EEPROMVID = EF2BYTE(*(__le16 *)&hwinfo[EEPROM_VID_88EU]);
		haldata->EEPROMPID = EF2BYTE(*(__le16 *)&hwinfo[EEPROM_PID_88EU]);

		/*  Customer ID, 0x00 and 0xff are reserved for Realtek. */
		haldata->EEPROMCustomerID = *(u8 *)&hwinfo[EEPROM_CUSTOMERID_88E];
		haldata->EEPROMSubCustomerID = EEPROM_Default_SubCustomerID;
	} else {
		haldata->EEPROMVID			= EEPROM_Default_VID;
		haldata->EEPROMPID			= EEPROM_Default_PID;

		/*  Customer ID, 0x00 and 0xff are reserved for Realtek. */
		haldata->EEPROMCustomerID		= EEPROM_Default_CustomerID;
		haldata->EEPROMSubCustomerID	= EEPROM_Default_SubCustomerID;
	}

	DBG_88E("VID = 0x%04X, PID = 0x%04X\n", haldata->EEPROMVID, haldata->EEPROMPID);
	DBG_88E("Customer ID: 0x%02X, SubCustomer ID: 0x%02X\n", haldata->EEPROMCustomerID, haldata->EEPROMSubCustomerID);
}