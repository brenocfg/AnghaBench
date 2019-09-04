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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_RATE ; 
 int /*<<< orphan*/  EE_9346CR ; 
 int _EEDO ; 
 int _FALSE ; 
 int _TRUE ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int rtw_read8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_udelay_os (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standby (int /*<<< orphan*/ *) ; 

u16 wait_eeprom_cmd_done(_adapter* padapter)
{
	u8 	x;
	u16	i,res=_FALSE;
_func_enter_;	
	standby(padapter );
	for (i=0; i<200; i++) 
	{
		x = rtw_read8(padapter, EE_9346CR);
		if (x & _EEDO){
			res=_TRUE;
			goto exit;
			}
		rtw_udelay_os(CLOCK_RATE);
	}
exit:	
_func_exit_;			
	return res;
}