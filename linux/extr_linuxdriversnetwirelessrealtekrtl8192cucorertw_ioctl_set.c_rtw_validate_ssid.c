#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int SsidLength; } ;
typedef  TYPE_1__ NDIS_802_11_SSID ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_set_c_ ; 

u8 rtw_validate_ssid(NDIS_802_11_SSID *ssid)
{
	u8	 i;
	u8	ret=_TRUE;

_func_enter_;	

	if (ssid->SsidLength > 32) {
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("ssid length >32\n"));
		ret= _FALSE;
		goto exit;
	}

#ifdef CONFIG_VALIDATE_SSID
	for(i = 0; i < ssid->SsidLength; i++)
	{
		//wifi, printable ascii code must be supported
		if(!( (ssid->Ssid[i] >= 0x20) && (ssid->Ssid[i] <= 0x7e) )){
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("ssid has nonprintabl ascii\n"));
			ret= _FALSE;
			break;
		}
	}
#endif /* CONFIG_VALIDATE_SSID */

exit:	

_func_exit_;

	return ret;
}