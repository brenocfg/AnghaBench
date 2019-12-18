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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCM_CHANNEL_FC ; 
 int /*<<< orphan*/  PCM_CHANNEL_FL ; 
 int /*<<< orphan*/  PCM_CHANNEL_FR ; 
 int /*<<< orphan*/  PCM_CHANNEL_LB ; 
 int /*<<< orphan*/  PCM_CHANNEL_LFE ; 
 int /*<<< orphan*/  PCM_CHANNEL_LS ; 
 int /*<<< orphan*/  PCM_CHANNEL_RB ; 
 int /*<<< orphan*/  PCM_CHANNEL_RS ; 
 int /*<<< orphan*/  PCM_MAX_NUM_CHANNEL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int q6dsp_map_channels(u8 ch_map[PCM_MAX_NUM_CHANNEL], int ch)
{
	memset(ch_map, 0, PCM_MAX_NUM_CHANNEL);

	switch (ch) {
	case 1:
		ch_map[0] = PCM_CHANNEL_FC;
		break;
	case 2:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		break;
	case 3:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		ch_map[2] = PCM_CHANNEL_FC;
		break;
	case 4:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		ch_map[2] = PCM_CHANNEL_LS;
		ch_map[3] = PCM_CHANNEL_RS;
		break;
	case 5:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		ch_map[2] = PCM_CHANNEL_FC;
		ch_map[3] = PCM_CHANNEL_LS;
		ch_map[4] = PCM_CHANNEL_RS;
		break;
	case 6:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		ch_map[2] = PCM_CHANNEL_LFE;
		ch_map[3] = PCM_CHANNEL_FC;
		ch_map[4] = PCM_CHANNEL_LS;
		ch_map[5] = PCM_CHANNEL_RS;
		break;
	case 8:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		ch_map[2] = PCM_CHANNEL_LFE;
		ch_map[3] = PCM_CHANNEL_FC;
		ch_map[4] = PCM_CHANNEL_LS;
		ch_map[5] = PCM_CHANNEL_RS;
		ch_map[6] = PCM_CHANNEL_LB;
		ch_map[7] = PCM_CHANNEL_RB;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}