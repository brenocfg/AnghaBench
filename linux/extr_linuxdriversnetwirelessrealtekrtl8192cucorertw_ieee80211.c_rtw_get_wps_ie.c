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
typedef  scalar_t__ uint ;
typedef  int u8 ;

/* Variables and functions */
 scalar_t__ _TRUE ; 
 int _WPA_IE_ID_ ; 
 scalar_t__ _rtw_memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  _rtw_memcpy (int*,int*,int) ; 

u8 *rtw_get_wps_ie(u8 *in_ie, uint in_len, u8 *wps_ie, uint *wps_ielen)
{
	uint cnt;
	u8 *wpsie_ptr=NULL;
	u8 eid, wps_oui[4]={0x0,0x50,0xf2,0x04};

	if(wps_ielen)
		*wps_ielen = 0;

	if(!in_ie || in_len<=0)
		return wpsie_ptr;

	cnt = 0;

	while(cnt<in_len)
	{
		eid = in_ie[cnt];

		if((eid==_WPA_IE_ID_)&&(_rtw_memcmp(&in_ie[cnt+2], wps_oui, 4)==_TRUE))
		{
			wpsie_ptr = &in_ie[cnt];

			if(wps_ie)
				_rtw_memcpy(wps_ie, &in_ie[cnt], in_ie[cnt+1]+2);
			
			if(wps_ielen)
				*wps_ielen = in_ie[cnt+1]+2;
			
			cnt+=in_ie[cnt+1]+2;

			break;
		}
		else
		{
			cnt+=in_ie[cnt+1]+2; //goto next	
		}		

	}	

	return wpsie_ptr;
}