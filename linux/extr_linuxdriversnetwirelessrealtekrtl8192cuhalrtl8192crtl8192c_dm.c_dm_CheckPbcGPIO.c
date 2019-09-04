#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_5__ {int /*<<< orphan*/  hw_wps_pbc; } ;
struct TYPE_6__ {scalar_t__* pid; scalar_t__ init_adpt_in_progress; TYPE_1__ registrypriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*,int) ; 
 int /*<<< orphan*/  GPIO_IN ; 
 scalar_t__ HAL_8192C_HW_GPIO_WPS_BIT ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  rtw_msleep_os (int) ; 
 scalar_t__ rtw_read8 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_CheckPbcGPIO(_adapter *padapter)
{	
	u8	tmp1byte;
	u8	bPbcPressed = _FALSE;
	int i=0;

	if(!padapter->registrypriv.hw_wps_pbc)
		return;

	do
	{
		i++;
#ifdef CONFIG_USB_HCI
	tmp1byte = rtw_read8(padapter, GPIO_IO_SEL);
	tmp1byte |= (HAL_8192C_HW_GPIO_WPS_BIT);
	rtw_write8(padapter, GPIO_IO_SEL, tmp1byte);	//enable GPIO[2] as output mode

	tmp1byte &= ~(HAL_8192C_HW_GPIO_WPS_BIT);
	rtw_write8(padapter,  GPIO_IN, tmp1byte);		//reset the floating voltage level

	tmp1byte = rtw_read8(padapter, GPIO_IO_SEL);
	tmp1byte &= ~(HAL_8192C_HW_GPIO_WPS_BIT);
	rtw_write8(padapter, GPIO_IO_SEL, tmp1byte);	//enable GPIO[2] as input mode

	tmp1byte =rtw_read8(padapter, GPIO_IN);
	
	if (tmp1byte == 0xff)
	{
		bPbcPressed = _FALSE;
		break ;
	}	

	if (tmp1byte&HAL_8192C_HW_GPIO_WPS_BIT)
	{
		bPbcPressed = _TRUE;

		if(i<=3)
			rtw_msleep_os(50);
	}
#else
	tmp1byte = rtw_read8(padapter, GPIO_IN);
	//RT_TRACE(COMP_IO, DBG_TRACE, ("dm_CheckPbcGPIO - %x\n", tmp1byte));

	if (tmp1byte == 0xff || padapter->init_adpt_in_progress)
	{
		bPbcPressed = _FALSE;
		break ;
	}

	if((tmp1byte&HAL_8192C_HW_GPIO_WPS_BIT)==0)
	{
		bPbcPressed = _TRUE;

		if(i<=3)
			rtw_msleep_os(50);
	}
#endif		

	}while(i<=3 && bPbcPressed == _TRUE);
	
	if( _TRUE == bPbcPressed)
	{
		// Here we only set bPbcPressed to true
		// After trigger PBC, the variable will be set to false		
		DBG_8192C("CheckPbcGPIO - PBC is pressed, try_cnt=%d\n", i-1);
                
#ifdef RTK_DMP_PLATFORM
#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,12))
		kobject_uevent(&padapter->pnetdev->dev.kobj, KOBJ_NET_PBC);
#else
		kobject_hotplug(&padapter->pnetdev->class_dev.kobj, KOBJ_NET_PBC);
#endif
#else

		if ( padapter->pid[0] == 0 )
		{	//	0 is the default value and it means the application monitors the HW PBC doesn't privde its pid to driver.
			return;
		}

#ifdef PLATFORM_LINUX
		rtw_signal_process(padapter->pid[0], SIGUSR1);
#endif
#endif
	}	
}