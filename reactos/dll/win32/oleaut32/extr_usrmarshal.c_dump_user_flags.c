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
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 int HIWORD (int /*<<< orphan*/  const) ; 
 int LOWORD (int /*<<< orphan*/  const) ; 
#define  MSHCTX_DIFFERENTMACHINE 131 
#define  MSHCTX_INPROC 130 
#define  MSHCTX_LOCAL 129 
#define  MSHCTX_NOSHAREDMEM 128 
 scalar_t__ NDR_LOCAL_DATA_REPRESENTATION ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static void dump_user_flags(const ULONG *pFlags)
{
    if (HIWORD(*pFlags) == NDR_LOCAL_DATA_REPRESENTATION)
        TRACE("MAKELONG(NDR_LOCAL_REPRESENTATION, ");
    else
        TRACE("MAKELONG(0x%04x, ", HIWORD(*pFlags));
    switch (LOWORD(*pFlags))
    {
        case MSHCTX_LOCAL: TRACE("MSHCTX_LOCAL)"); break;
        case MSHCTX_NOSHAREDMEM: TRACE("MSHCTX_NOSHAREDMEM)"); break;
        case MSHCTX_DIFFERENTMACHINE: TRACE("MSHCTX_DIFFERENTMACHINE)"); break;
        case MSHCTX_INPROC: TRACE("MSHCTX_INPROC)"); break;
        default: TRACE("%d)", LOWORD(*pFlags));
    }
}