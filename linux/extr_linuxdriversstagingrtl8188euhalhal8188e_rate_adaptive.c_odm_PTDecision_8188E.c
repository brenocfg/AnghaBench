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
typedef  int u8 ;
typedef  int u32 ;
struct odm_ra_info {int TOTAL; int* RTY; int PTStage; int PTSmoothFactor; int DROP; } ;

/* Variables and functions */
 int* PT_PENALTY ; 

__attribute__((used)) static void odm_PTDecision_8188E(struct odm_ra_info *pRaInfo)
{
	u8 j;
	u8 temp_stage;
	u32 numsc;
	u32 num_total;
	u8 stage_id;

	numsc  = 0;
	num_total = pRaInfo->TOTAL * PT_PENALTY[5];
	for (j = 0; j <= 4; j++) {
		numsc += pRaInfo->RTY[j] * PT_PENALTY[j];
		if (numsc > num_total)
			break;
	}

	j >>= 1;
	temp_stage = (pRaInfo->PTStage + 1) >> 1;
	if (temp_stage > j)
		stage_id = temp_stage-j;
	else
		stage_id = 0;

	pRaInfo->PTSmoothFactor = (pRaInfo->PTSmoothFactor>>1) + (pRaInfo->PTSmoothFactor>>2) + stage_id*16+2;
	if (pRaInfo->PTSmoothFactor > 192)
		pRaInfo->PTSmoothFactor = 192;
	stage_id = pRaInfo->PTSmoothFactor >> 6;
	temp_stage = stage_id*2;
	if (temp_stage != 0)
		temp_stage -= 1;
	if (pRaInfo->DROP > 3)
		temp_stage = 0;
	pRaInfo->PTStage = temp_stage;
}