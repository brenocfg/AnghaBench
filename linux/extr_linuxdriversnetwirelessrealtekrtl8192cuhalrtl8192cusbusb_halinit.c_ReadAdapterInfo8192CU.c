#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  EepromAddressSize; } ;
typedef  TYPE_1__* PADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  GetEEPROMSize8192C (TYPE_1__*) ; 
 int /*<<< orphan*/  _ReadAdapterInfo8192CU (TYPE_1__*) ; 

__attribute__((used)) static void ReadAdapterInfo8192CU(PADAPTER Adapter)
{
	// Read EEPROM size before call any EEPROM function
	//Adapter->EepromAddressSize=Adapter->HalFunc.GetEEPROMSizeHandler(Adapter);
	Adapter->EepromAddressSize = GetEEPROMSize8192C(Adapter);
	
	_ReadAdapterInfo8192CU(Adapter);
}