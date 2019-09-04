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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  odm_InbandNoise_Monitor_NSeries (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s16 ODM_InbandNoise_Monitor(void *pDM_VOID, u8 bPauseDIG, u8 IGIValue, u32 max_time)
{
	return odm_InbandNoise_Monitor_NSeries(pDM_VOID, bPauseDIG, IGIValue, max_time);
}