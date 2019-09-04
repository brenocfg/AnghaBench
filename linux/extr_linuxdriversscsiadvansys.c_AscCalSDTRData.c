#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uchar ;
struct TYPE_4__ {int max_sdtr_index; } ;
typedef  TYPE_1__ ASC_DVC_VAR ;

/* Variables and functions */
 int ASC_SYN_MAX_OFFSET ; 
 int AscGetSynPeriodIndex (TYPE_1__*,int) ; 

__attribute__((used)) static uchar
AscCalSDTRData(ASC_DVC_VAR *asc_dvc, uchar sdtr_period, uchar syn_offset)
{
	uchar byte;
	uchar sdtr_period_ix;

	sdtr_period_ix = AscGetSynPeriodIndex(asc_dvc, sdtr_period);
	if (sdtr_period_ix > asc_dvc->max_sdtr_index)
		return 0xFF;
	byte = (sdtr_period_ix << 4) | (syn_offset & ASC_SYN_MAX_OFFSET);
	return byte;
}