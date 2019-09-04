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
typedef  int s32 ;
typedef  int /*<<< orphan*/  _adapter ;
struct TYPE_3__ {scalar_t__ CustomerID; } ;
typedef  TYPE_1__ HAL_DATA_TYPE ;

/* Variables and functions */
 TYPE_1__* GET_HAL_DATA (int /*<<< orphan*/ *) ; 
 scalar_t__ RT_CID_819x_Lenovo ; 

__attribute__((used)) static s32 signal_scale_mapping(_adapter *padapter, s32 cur_sig )
{
	s32 ret_sig;

#ifdef CONFIG_USB_HCI
	if(cur_sig >= 51 && cur_sig <= 100)
	{
		ret_sig = 100;
	}
	else if(cur_sig >= 41 && cur_sig <= 50)
	{
		ret_sig = 80 + ((cur_sig - 40)*2);
	}
	else if(cur_sig >= 31 && cur_sig <= 40)
	{
		ret_sig = 66 + (cur_sig - 30);
	}
	else if(cur_sig >= 21 && cur_sig <= 30)
	{
		ret_sig = 54 + (cur_sig - 20);
	}
	else if(cur_sig >= 10 && cur_sig <= 20)
	{
		ret_sig = 42 + (((cur_sig - 10) * 2) / 3);
	}
	else if(cur_sig >= 5 && cur_sig <= 9)
	{
		ret_sig = 22 + (((cur_sig - 5) * 3) / 2);
	}
	else if(cur_sig >= 1 && cur_sig <= 4)
	{
		ret_sig = 6 + (((cur_sig - 1) * 3) / 2);
	}
	else
	{
		ret_sig = cur_sig;
	}
#else
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);

	if(pHalData->CustomerID == RT_CID_819x_Lenovo)
	{
		// Step 1. Scale mapping.
		// 20100611 Joseph: Re-tunning RSSI presentation for Lenovo.
		// 20100426 Joseph: Modify Signal strength mapping.
		// This modification makes the RSSI indication similar to Intel solution.
		// 20100414 Joseph: Tunning RSSI for Lenovo according to RTL8191SE.
		if(cur_sig >= 54 && cur_sig <= 100)
		{
			ret_sig = 100;
		}
		else if(cur_sig>=42 && cur_sig <= 53 )
		{
			ret_sig = 95;
		}
		else if(cur_sig>=36 && cur_sig <= 41 )
		{
			ret_sig = 74 + ((cur_sig - 36) *20)/6;
		}
		else if(cur_sig>=33 && cur_sig <= 35 )
		{
			ret_sig = 65 + ((cur_sig - 33) *8)/2;
		}
		else if(cur_sig>=18 && cur_sig <= 32 )
		{
			ret_sig = 62 + ((cur_sig - 18) *2)/15;
		}
		else if(cur_sig>=15 && cur_sig <= 17 )
		{
			ret_sig = 33 + ((cur_sig - 15) *28)/2;
		}
		else if(cur_sig>=10 && cur_sig <= 14 )
		{
			ret_sig = 39;
		}
		else if(cur_sig>=8 && cur_sig <= 9 )
		{
			ret_sig = 33;
		}
		else if(cur_sig <= 8 )
		{
			ret_sig = 19;
		}
	}
	else
	{
		// Step 1. Scale mapping.
		if(cur_sig >= 61 && cur_sig <= 100)
		{
			ret_sig = 90 + ((cur_sig - 60) / 4);
		}
		else if(cur_sig >= 41 && cur_sig <= 60)
		{
			ret_sig = 78 + ((cur_sig - 40) / 2);
		}
		else if(cur_sig >= 31 && cur_sig <= 40)
		{
			ret_sig = 66 + (cur_sig - 30);
		}
		else if(cur_sig >= 21 && cur_sig <= 30)
		{
			ret_sig = 54 + (cur_sig - 20);
		}
		else if(cur_sig >= 5 && cur_sig <= 20)
		{
			ret_sig = 42 + (((cur_sig - 5) * 2) / 3);
		}
		else if(cur_sig == 4)
		{
			ret_sig = 36;
		}
		else if(cur_sig == 3)
		{
			ret_sig = 27;
		}
		else if(cur_sig == 2)
		{
			ret_sig = 18;
		}
		else if(cur_sig == 1)
		{
			ret_sig = 9;
		}
		else
		{
			ret_sig = cur_sig;
		}
	}
#endif

	return ret_sig;
}