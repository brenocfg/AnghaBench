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
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 int /*<<< orphan*/  IFX_MEI_LongWordWriteOffset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ME_DBG_DATA ; 
 scalar_t__ ME_DBG_DECODE ; 
 scalar_t__ ME_DBG_WR_AD ; 
 int /*<<< orphan*/  meiPollForDbgDone (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DSL_DEV_MeiError_t
_IFX_MEI_DBGLongWordWrite (DSL_DEV_Device_t * pDev, u32 DEC_mode,
				 u32 address, u32 data)
{
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_DBG_DECODE, DEC_mode);
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_DBG_WR_AD, address);
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_DBG_DATA, data);
	meiPollForDbgDone (pDev);
	return DSL_DEV_MEI_ERR_SUCCESS;
}