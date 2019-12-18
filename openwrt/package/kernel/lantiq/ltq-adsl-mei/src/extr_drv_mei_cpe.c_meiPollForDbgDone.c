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
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int ARC_TO_MEI_DBG_DONE ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordReadOffset (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordWriteOffset (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ME_ARC2ME_STAT ; 
 int WHILE_DELAY ; 

__attribute__((used)) static void
meiPollForDbgDone (DSL_DEV_Device_t * pDev)
{
	u32 query = 0;
	int i = 0;

	while (i < WHILE_DELAY) {
		IFX_MEI_LongWordReadOffset (pDev, (u32) ME_ARC2ME_STAT,  &query);
		query &= (ARC_TO_MEI_DBG_DONE);
		if (query)
			break;
		i++;
		if (i == WHILE_DELAY) {
			IFX_MEI_EMSG ("PollforDbg fail!\n");
		}
	}
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_ARC2ME_STAT, ARC_TO_MEI_DBG_DONE);	// to clear this interrupt
}