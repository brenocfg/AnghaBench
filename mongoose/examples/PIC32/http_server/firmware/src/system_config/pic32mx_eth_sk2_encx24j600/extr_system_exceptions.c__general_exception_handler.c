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

/* Variables and functions */
 int /*<<< orphan*/  SYS_DEBUG_BreakPoint () ; 
 int /*<<< orphan*/  SYS_DEBUG_PRINT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ERROR_ERROR ; 
 int _CP0_GET_CAUSE () ; 
 int /*<<< orphan*/  _CP0_GET_EPC () ; 
 int /*<<< orphan*/  _cause_str ; 
 int /*<<< orphan*/  _excep_addr ; 
 size_t _excep_code ; 
 int /*<<< orphan*/ * cause ; 

void _general_exception_handler ( void )
{
    /* Mask off Mask of the ExcCode Field from the Cause Register
    Refer to the MIPs Software User's manual */
    _excep_code = (_CP0_GET_CAUSE() & 0x0000007C) >> 2;
    _excep_addr = _CP0_GET_EPC();
    _cause_str  = cause[_excep_code];

    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "\nGeneral Exception %s (cause=%d, addr=%x).\n",
                    _cause_str, _excep_code, _excep_addr);

    while (1)
    {
        SYS_DEBUG_BreakPoint();
    }
}