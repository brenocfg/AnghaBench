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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct eeprom_priv {int /*<<< orphan*/ * efuse_eeprom_data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct eeprom_priv* GET_EEPROM_EFUSE_PRIV (struct adapter*) ; 

__attribute__((used)) static void
efuse_ShadowRead1Byte(
struct adapter *padapter,
u16 	Offset,
	u8 *Value)
{
	struct eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	*Value = pEEPROM->efuse_eeprom_data[Offset];

}