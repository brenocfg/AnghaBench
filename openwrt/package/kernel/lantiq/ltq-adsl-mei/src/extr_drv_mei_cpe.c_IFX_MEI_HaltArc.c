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
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_DEBUG ; 
 int ARC_DEBUG_HALT ; 
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 int /*<<< orphan*/  IFX_MEI_ControlModeSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JTAG_MASTER_MODE ; 
 int /*<<< orphan*/  MEI_DEBUG_DEC_AUX_MASK ; 
 int /*<<< orphan*/  MEI_MASTER_MODE ; 
 int /*<<< orphan*/  MEI_WAIT (int) ; 
 int /*<<< orphan*/  _IFX_MEI_DBGLongWordRead (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  _IFX_MEI_DBGLongWordWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static DSL_DEV_MeiError_t
IFX_MEI_HaltArc (DSL_DEV_Device_t * pDev)
{
	u32 arc_debug_data = 0x0;

	//      Switch arc control from JTAG mode to MEI mode
	IFX_MEI_ControlModeSet (pDev, MEI_MASTER_MODE);
	_IFX_MEI_DBGLongWordRead (pDev, MEI_DEBUG_DEC_AUX_MASK,
					ARC_DEBUG, &arc_debug_data);
	arc_debug_data |= ARC_DEBUG_HALT;
	_IFX_MEI_DBGLongWordWrite (pDev, MEI_DEBUG_DEC_AUX_MASK,
					 ARC_DEBUG, arc_debug_data);
	//      Switch arc control from MEI mode to JTAG mode
	IFX_MEI_ControlModeSet (pDev, JTAG_MASTER_MODE);

	MEI_WAIT (10);

	return DSL_DEV_MEI_ERR_SUCCESS;
}