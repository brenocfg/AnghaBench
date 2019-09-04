#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {int bSurpriseRemoved; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  EE_9346CR ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _EEDI ; 
 int _EEDO ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_eeprom_c_ ; 
 int /*<<< orphan*/  down_clk (TYPE_1__*,int*) ; 
 int rtw_read8 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_clk (TYPE_1__*,int*) ; 

u16 shift_in_bits(_adapter *padapter)
{
	u16 x, d = 0, i;
_func_enter_;
	if (padapter->bSurpriseRemoved == true) {
		RT_TRACE(_module_rtl871x_eeprom_c_, _drv_err_, ("padapter->bSurpriseRemoved==true"));
		goto out;
	}
	x = rtw_read8(padapter, EE_9346CR);

	x &= ~(_EEDO | _EEDI);
	d = 0;

	for (i = 0; i < 16; i++) {
		d = d << 1;
		up_clk(padapter, &x);
	if (padapter->bSurpriseRemoved == true) {
		RT_TRACE(_module_rtl871x_eeprom_c_, _drv_err_, ("padapter->bSurpriseRemoved==true"));
		goto out;
	}
		x = rtw_read8(padapter, EE_9346CR);

		x &= ~(_EEDI);
		if (x & _EEDO)
		d |= 1;

		down_clk(padapter, &x);
	}
out:
_func_exit_;

	return d;
}