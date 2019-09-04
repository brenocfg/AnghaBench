#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct rtllib_device {int bGlobalDomain; int IbssStartChnl; int ibss_maxjoin_chal; } ;
struct TYPE_4__ {int Len; int* Channel; } ;
struct TYPE_3__ {int* channel_map; } ;

/* Variables and functions */
#define  COUNTRY_CODE_GLOBAL_DOMAIN 129 
#define  COUNTRY_CODE_WORLD_WIDE_13 128 
 TYPE_2__* ChannelPlan ; 
 TYPE_1__* GET_DOT11D_INFO (struct rtllib_device*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void Dot11d_Channelmap(u8 channel_plan, struct rtllib_device *ieee)
{
	int i, max_chan = 14, min_chan = 1;

	ieee->bGlobalDomain = false;

	if (ChannelPlan[channel_plan].Len != 0) {
		memset(GET_DOT11D_INFO(ieee)->channel_map, 0,
		       sizeof(GET_DOT11D_INFO(ieee)->channel_map));
		for (i = 0; i < ChannelPlan[channel_plan].Len; i++) {
			if (ChannelPlan[channel_plan].Channel[i] < min_chan ||
			    ChannelPlan[channel_plan].Channel[i] > max_chan)
				break;
			GET_DOT11D_INFO(ieee)->channel_map[ChannelPlan
					[channel_plan].Channel[i]] = 1;
		}
	}

	switch (channel_plan) {
	case COUNTRY_CODE_GLOBAL_DOMAIN:
		ieee->bGlobalDomain = true;
		for (i = 12; i <= 14; i++)
			GET_DOT11D_INFO(ieee)->channel_map[i] = 2;
		ieee->IbssStartChnl = 10;
		ieee->ibss_maxjoin_chal = 11;
		break;

	case COUNTRY_CODE_WORLD_WIDE_13:
		for (i = 12; i <= 13; i++)
			GET_DOT11D_INFO(ieee)->channel_map[i] = 2;
		ieee->IbssStartChnl = 10;
		ieee->ibss_maxjoin_chal = 11;
		break;

	default:
		ieee->IbssStartChnl = 1;
		ieee->ibss_maxjoin_chal = 14;
		break;
	}
}