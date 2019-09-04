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
 int /*<<< orphan*/  RSSI_SETTING_EID ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192c_FillH2CCmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

u8 rtl8192c_set_rssi_cmd(_adapter*padapter, u8 *param)
{	
	u8	res=_SUCCESS;

_func_enter_;

	*((u32*) param ) = cpu_to_le32( *((u32*) param ) );

	rtl8192c_FillH2CCmd(padapter, RSSI_SETTING_EID, 3, param);

_func_exit_;

	return res;
}