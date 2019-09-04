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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  write_cam (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 

void clear_cam_entry(_adapter *padapter, u8 entry)
{	
#if 0
	u32	addr, val=0;
	u32	cam_val[2];

	addr = entry << 3;
	

	cam_val[0] = val;
	cam_val[1] = addr + (unsigned int)0;

	rtw_hal_set_hwreg(padapter, HW_VAR_CAM_WRITE, (u8 *)cam_val);



	cam_val[0] = val;
	cam_val[1] = addr + (unsigned int)1;

	rtw_hal_set_hwreg(padapter, HW_VAR_CAM_WRITE, (u8 *)cam_val);
#else

	unsigned char null_sta[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	unsigned char null_key[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00};

	write_cam(padapter, entry, 0, null_sta, null_key);

#endif
}