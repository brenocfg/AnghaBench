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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  DSL_uint32_t ;
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;
typedef  int DSL_BSP_MemoryAccessType_t ;

/* Variables and functions */
#define  DSL_BSP_MEMORY_READ 129 
#define  DSL_BSP_MEMORY_WRITE 128 
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 int /*<<< orphan*/  IFX_MEI_DebugRead (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_MEI_DebugWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

DSL_DEV_MeiError_t
DSL_BSP_MemoryDebugAccess (DSL_DEV_Device_t * pDev,
				DSL_BSP_MemoryAccessType_t type,
				DSL_uint32_t destaddr, DSL_uint32_t *databuff,
				DSL_uint32_t databuffsize)
{
	DSL_DEV_MeiError_t meierr = DSL_DEV_MEI_ERR_SUCCESS;
	switch (type) {
	case DSL_BSP_MEMORY_READ:
		meierr = IFX_MEI_DebugRead (pDev, (u32)destaddr, (u32*)databuff, (u32)databuffsize);
		break;
	case DSL_BSP_MEMORY_WRITE:
		meierr = IFX_MEI_DebugWrite (pDev, (u32)destaddr, (u32*)databuff, (u32)databuffsize);
		break;
	}
	return DSL_DEV_MEI_ERR_SUCCESS;
}