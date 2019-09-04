#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_9__ {int EepromAddressSize; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_EWDS_OPCODE ; 
 int /*<<< orphan*/  EEPROM_EWEN_OPCODE ; 
 int /*<<< orphan*/  EEPROM_WRITE_OPCODE ; 
 int /*<<< orphan*/  EE_9346CR ; 
 int _EECS ; 
 int _EEDI ; 
 int _EEDO ; 
 int _EEM0 ; 
 int _EEM1 ; 
 int _EESK ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  eeprom_clean (TYPE_1__*) ; 
 int rtw_read8 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shift_out_bits (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  standby (TYPE_1__*) ; 
 int wait_eeprom_cmd_done (TYPE_1__*) ; 

void eeprom_write16(_adapter *padapter, u16 reg, u16 data)
{
	u8 x;

_func_enter_;

	x = rtw_read8(padapter, EE_9346CR);

	x &= ~(_EEDI | _EEDO | _EESK | _EEM0);
	x |= _EEM1 | _EECS;
	rtw_write8(padapter, EE_9346CR, x);

	shift_out_bits(padapter, EEPROM_EWEN_OPCODE, 5);

	if (padapter->EepromAddressSize == 8)	/*CF+ and SDIO*/
		shift_out_bits(padapter, 0, 6);
	else									/*USB*/
		shift_out_bits(padapter, 0, 4);

	standby(padapter);

/* Commented out by rcnjko, 2004.0
*	 Erase this particular word.  Write the erase opcode and register
*	 number in that order. The opcode is 3bits in length; reg is 6 bits long.
*	shift_out_bits(Adapter, EEPROM_ERASE_OPCODE, 3);
*	shift_out_bits(Adapter, reg, Adapter->EepromAddressSize);
*
*	if (wait_eeprom_cmd_done(Adapter ) == false)
*	{
*		return;
*	}
*/

	standby(padapter);

	/* write the new word to the EEPROM*/

	/* send the write opcode the EEPORM*/
	shift_out_bits(padapter, EEPROM_WRITE_OPCODE, 3);

	/* select which word in the EEPROM that we are writing to.*/
	shift_out_bits(padapter, reg, padapter->EepromAddressSize);

	/* write the data to the selected EEPROM word.*/
	shift_out_bits(padapter, data, 16);

	if (wait_eeprom_cmd_done(padapter) == false) {

		goto exit;
	}

	standby(padapter);

	shift_out_bits(padapter, EEPROM_EWDS_OPCODE, 5);
	shift_out_bits(padapter, reg, 4);

	eeprom_clean(padapter);
exit:
_func_exit_;
	return;
}