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
struct adapter {int /*<<< orphan*/  EepromAddressSize; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetEEPROMSize8723B (struct adapter*) ; 
 int /*<<< orphan*/  _ReadAdapterInfo8723BS (struct adapter*) ; 

__attribute__((used)) static void ReadAdapterInfo8723BS(struct adapter *padapter)
{
	/*  Read EEPROM size before call any EEPROM function */
	padapter->EepromAddressSize = GetEEPROMSize8723B(padapter);

	_ReadAdapterInfo8723BS(padapter);
}