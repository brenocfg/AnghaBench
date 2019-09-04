#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  scalar_t__ u8 ;
struct TYPE_4__ {scalar_t__ cur_channel; } ;
struct TYPE_5__ {TYPE_1__ mlmeextpriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int WLAN_HDR_A3_LEN ; 
 int _BEACON_IE_OFFSET_ ; 
 int /*<<< orphan*/  _DSSET_IE_ ; 
 scalar_t__* rtw_get_ie (scalar_t__*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static u8 cmp_pkt_chnl_diff(_adapter *padapter,u8* pframe,uint packet_len)
{	// if the channel is same, return 0. else return channel differential	
	uint len;
	u8 channel;	
	u8 *p;		
	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + _BEACON_IE_OFFSET_, _DSSET_IE_, &len, packet_len - _BEACON_IE_OFFSET_);	
	if (p)	
	{	
		channel = *(p + 2);		
		if(padapter->mlmeextpriv.cur_channel >= channel)		
		{			
			return (padapter->mlmeextpriv.cur_channel - channel);		
		}		
		else		
		{			
			return (channel-padapter->mlmeextpriv.cur_channel);		
		}	
	}	
	else
	{		
		return 0;	
	}
}