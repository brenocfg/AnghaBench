#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct rt_channel_info {int ChannelNum; void* ScanType; } ;
struct TYPE_5__ {int wireless_mode; } ;
struct adapter {TYPE_1__ registrypriv; } ;
struct TYPE_8__ {size_t Index2G; } ;
struct TYPE_7__ {size_t Len; int* Channel; } ;
struct TYPE_6__ {size_t Index2G; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,size_t) ; 
 int MAX_CHANNEL_NUM ; 
 TYPE_4__ RTW_CHANNEL_PLAN_MAP_REALTEK_DEFINE ; 
 TYPE_3__* RTW_ChannelPlan2G ; 
 TYPE_2__* RTW_ChannelPlanMap ; 
 size_t RT_CHANNEL_DOMAIN_2G_WORLD ; 
 size_t RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN ; 
 size_t RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN_2G ; 
 size_t RT_CHANNEL_DOMAIN_MAX ; 
 size_t RT_CHANNEL_DOMAIN_REALTEK_DEFINE ; 
 size_t RT_CHANNEL_DOMAIN_WORLD_WIDE_13 ; 
 void* SCAN_ACTIVE ; 
 void* SCAN_PASSIVE ; 
 int WIRELESS_11G ; 
 int /*<<< orphan*/  memset (struct rt_channel_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 init_channel_set(struct adapter *padapter, u8 ChannelPlan,
			   struct rt_channel_info *channel_set)
{
	u8 index, chanset_size = 0;
	u8 b2_4GBand = false;
	u8 Index2G = 0;

	memset(channel_set, 0, sizeof(struct rt_channel_info) * MAX_CHANNEL_NUM);

	if (ChannelPlan >= RT_CHANNEL_DOMAIN_MAX && ChannelPlan != RT_CHANNEL_DOMAIN_REALTEK_DEFINE) {
		DBG_88E("ChannelPlan ID %x error !!!!!\n", ChannelPlan);
		return chanset_size;
	}

	if (padapter->registrypriv.wireless_mode & WIRELESS_11G) {
		b2_4GBand = true;
		if (ChannelPlan == RT_CHANNEL_DOMAIN_REALTEK_DEFINE)
			Index2G = RTW_CHANNEL_PLAN_MAP_REALTEK_DEFINE.Index2G;
		else
			Index2G = RTW_ChannelPlanMap[ChannelPlan].Index2G;
	}

	if (b2_4GBand) {
		for (index = 0; index < RTW_ChannelPlan2G[Index2G].Len; index++) {
			channel_set[chanset_size].ChannelNum = RTW_ChannelPlan2G[Index2G].Channel[index];

			if ((ChannelPlan == RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN) ||/* Channel 1~11 is active, and 12~14 is passive */
			    (ChannelPlan == RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN_2G)) {
				if (channel_set[chanset_size].ChannelNum >= 1 && channel_set[chanset_size].ChannelNum <= 11)
					channel_set[chanset_size].ScanType = SCAN_ACTIVE;
				else if ((channel_set[chanset_size].ChannelNum  >= 12 && channel_set[chanset_size].ChannelNum  <= 14))
					channel_set[chanset_size].ScanType  = SCAN_PASSIVE;
			} else if (ChannelPlan == RT_CHANNEL_DOMAIN_WORLD_WIDE_13 ||
				   Index2G == RT_CHANNEL_DOMAIN_2G_WORLD) {/*  channel 12~13, passive scan */
				if (channel_set[chanset_size].ChannelNum <= 11)
					channel_set[chanset_size].ScanType = SCAN_ACTIVE;
				else
					channel_set[chanset_size].ScanType = SCAN_PASSIVE;
			} else {
				channel_set[chanset_size].ScanType = SCAN_ACTIVE;
			}

			chanset_size++;
		}
	}
	return chanset_size;
}