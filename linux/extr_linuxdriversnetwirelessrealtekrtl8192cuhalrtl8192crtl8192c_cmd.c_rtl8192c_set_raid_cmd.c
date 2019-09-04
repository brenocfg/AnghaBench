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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  MACID_CONFIG_EID ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192c_FillH2CCmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

u8 rtl8192c_set_raid_cmd(_adapter*padapter, u32 mask, u8 arg)
{	
	u8	buf[5];
	u8	res=_SUCCESS;
	
_func_enter_;	
	
	_rtw_memset(buf, 0, 5);
	mask = cpu_to_le32( mask );
	_rtw_memcpy(buf, &mask, 4);
	buf[4]  = arg;

	rtl8192c_FillH2CCmd(padapter, MACID_CONFIG_EID, 5, buf);
	
_func_exit_;

	return res;

}