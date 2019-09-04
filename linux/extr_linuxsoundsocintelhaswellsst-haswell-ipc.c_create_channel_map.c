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
typedef  int u32 ;
typedef  enum sst_hsw_channel_config { ____Placeholder_sst_hsw_channel_config } sst_hsw_channel_config ;

/* Variables and functions */
 int SST_HSW_CHANNEL_CENTER ; 
 int SST_HSW_CHANNEL_CENTER_SURROUND ; 
#define  SST_HSW_CHANNEL_CONFIG_2_POINT_1 137 
#define  SST_HSW_CHANNEL_CONFIG_3_POINT_0 136 
#define  SST_HSW_CHANNEL_CONFIG_3_POINT_1 135 
#define  SST_HSW_CHANNEL_CONFIG_4_POINT_0 134 
#define  SST_HSW_CHANNEL_CONFIG_5_POINT_0 133 
#define  SST_HSW_CHANNEL_CONFIG_5_POINT_1 132 
#define  SST_HSW_CHANNEL_CONFIG_DUAL_MONO 131 
#define  SST_HSW_CHANNEL_CONFIG_MONO 130 
#define  SST_HSW_CHANNEL_CONFIG_QUATRO 129 
#define  SST_HSW_CHANNEL_CONFIG_STEREO 128 
 int SST_HSW_CHANNEL_LEFT ; 
 int SST_HSW_CHANNEL_LEFT_SURROUND ; 
 int SST_HSW_CHANNEL_LFE ; 
 int SST_HSW_CHANNEL_RIGHT ; 
 int SST_HSW_CHANNEL_RIGHT_SURROUND ; 

u32 create_channel_map(enum sst_hsw_channel_config config)
{
	switch (config) {
	case SST_HSW_CHANNEL_CONFIG_MONO:
		return (0xFFFFFFF0 | SST_HSW_CHANNEL_CENTER);
	case SST_HSW_CHANNEL_CONFIG_STEREO:
		return (0xFFFFFF00 | SST_HSW_CHANNEL_LEFT
			| (SST_HSW_CHANNEL_RIGHT << 4));
	case SST_HSW_CHANNEL_CONFIG_2_POINT_1:
		return (0xFFFFF000 | SST_HSW_CHANNEL_LEFT
			| (SST_HSW_CHANNEL_RIGHT << 4)
			| (SST_HSW_CHANNEL_LFE << 8 ));
	case SST_HSW_CHANNEL_CONFIG_3_POINT_0:
		return (0xFFFFF000 | SST_HSW_CHANNEL_LEFT
			| (SST_HSW_CHANNEL_CENTER << 4)
			| (SST_HSW_CHANNEL_RIGHT << 8));
	case SST_HSW_CHANNEL_CONFIG_3_POINT_1:
		return (0xFFFF0000 | SST_HSW_CHANNEL_LEFT
			| (SST_HSW_CHANNEL_CENTER << 4)
			| (SST_HSW_CHANNEL_RIGHT << 8)
			| (SST_HSW_CHANNEL_LFE << 12));
	case SST_HSW_CHANNEL_CONFIG_QUATRO:
		return (0xFFFF0000 | SST_HSW_CHANNEL_LEFT
			| (SST_HSW_CHANNEL_RIGHT << 4)
			| (SST_HSW_CHANNEL_LEFT_SURROUND << 8)
			| (SST_HSW_CHANNEL_RIGHT_SURROUND << 12));
	case SST_HSW_CHANNEL_CONFIG_4_POINT_0:
		return (0xFFFF0000 | SST_HSW_CHANNEL_LEFT
			| (SST_HSW_CHANNEL_CENTER << 4)
			| (SST_HSW_CHANNEL_RIGHT << 8)
			| (SST_HSW_CHANNEL_CENTER_SURROUND << 12));
	case SST_HSW_CHANNEL_CONFIG_5_POINT_0:
		return (0xFFF00000 | SST_HSW_CHANNEL_LEFT
			| (SST_HSW_CHANNEL_CENTER << 4)
			| (SST_HSW_CHANNEL_RIGHT << 8)
			| (SST_HSW_CHANNEL_LEFT_SURROUND << 12)
			| (SST_HSW_CHANNEL_RIGHT_SURROUND << 16));
	case SST_HSW_CHANNEL_CONFIG_5_POINT_1:
		return (0xFF000000 | SST_HSW_CHANNEL_CENTER
			| (SST_HSW_CHANNEL_LEFT << 4)
			| (SST_HSW_CHANNEL_RIGHT << 8)
			| (SST_HSW_CHANNEL_LEFT_SURROUND << 12)
			| (SST_HSW_CHANNEL_RIGHT_SURROUND << 16)
			| (SST_HSW_CHANNEL_LFE << 20));
	case SST_HSW_CHANNEL_CONFIG_DUAL_MONO:
		return (0xFFFFFF00 | SST_HSW_CHANNEL_LEFT
			| (SST_HSW_CHANNEL_LEFT << 4));
	default:
		return 0xFFFFFFFF;
	}
}