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
typedef  int uint32_t ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ address; scalar_t__ size; int /*<<< orphan*/  org_address; } ;
typedef  TYPE_1__ smmu_mem_info_t ;
struct TYPE_4__ {TYPE_1__* adsl_mem_info; } ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int DSL_DEV_MEI_ERR_SUCCESS ; 
 TYPE_2__* DSL_DEV_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordWriteOffset (int /*<<< orphan*/ *,scalar_t__,unsigned long) ; 
 int MAX_BAR_REGISTERS ; 
 scalar_t__ ME_XDATA_BASE_SH ; 
 scalar_t__ ME_XMEM_BAR_BASE ; 
 int XDATA_REGISTER ; 
 scalar_t__ g_xdata_addr ; 

__attribute__((used)) static int
IFX_MEI_BarUpdate (DSL_DEV_Device_t * pDev, int nTotalBar)
{
	int idx = 0;
	smmu_mem_info_t *adsl_mem_info =
		DSL_DEV_PRIVATE(pDev)->adsl_mem_info;

	for (idx = 0; idx < nTotalBar; idx++) {
		//skip XDATA register
		if (idx == XDATA_REGISTER)
			continue;
		IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_XMEM_BAR_BASE + idx * 4,
			(((uint32_t) adsl_mem_info[idx].address) & 0x0FFFFFFF));
	}
	for (idx = nTotalBar; idx < MAX_BAR_REGISTERS; idx++) {
		if (idx == XDATA_REGISTER)
			continue;
		IFX_MEI_LongWordWriteOffset (pDev,  (u32) ME_XMEM_BAR_BASE  + idx * 4,
			 (((uint32_t)adsl_mem_info[nTotalBar - 1].address) & 0x0FFFFFFF));
		/* These are for /proc/danube_mei/meminfo purpose */
		adsl_mem_info[idx].address = adsl_mem_info[nTotalBar - 1].address;
		adsl_mem_info[idx].org_address = adsl_mem_info[nTotalBar - 1].org_address;
		adsl_mem_info[idx].size = 0; /* Prevent it from being freed */
	}

    g_xdata_addr = adsl_mem_info[XDATA_REGISTER].address;
	IFX_MEI_LongWordWriteOffset (pDev,  (u32) ME_XMEM_BAR_BASE  + XDATA_REGISTER * 4,
		(((uint32_t) adsl_mem_info [XDATA_REGISTER].address) & 0x0FFFFFFF));
	// update MEI_XDATA_BASE_SH
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_XDATA_BASE_SH,
		 ((unsigned long)adsl_mem_info[XDATA_REGISTER].address) & 0x0FFFFFFF);

	return DSL_DEV_MEI_ERR_SUCCESS;
}