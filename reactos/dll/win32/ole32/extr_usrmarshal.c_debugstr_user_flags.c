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
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
#define  MSHCTX_DIFFERENTMACHINE 131 
#define  MSHCTX_INPROC 130 
#define  MSHCTX_LOCAL 129 
#define  MSHCTX_NOSHAREDMEM 128 
 scalar_t__ NDR_LOCAL_DATA_REPRESENTATION ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char const* wine_dbg_sprintf (char*,char const*,...) ; 

__attribute__((used)) static const char* debugstr_user_flags(ULONG *pFlags)
{
    char buf[12];
    const char* loword;
    switch (LOWORD(*pFlags))
    {
    case MSHCTX_LOCAL:
        loword="MSHCTX_LOCAL";
        break;
    case MSHCTX_NOSHAREDMEM:
        loword="MSHCTX_NOSHAREDMEM";
        break;
    case MSHCTX_DIFFERENTMACHINE:
        loword="MSHCTX_DIFFERENTMACHINE";
        break;
    case MSHCTX_INPROC:
        loword="MSHCTX_INPROC";
        break;
    default:
        sprintf(buf, "%d", LOWORD(*pFlags));
        loword=buf;
    }

    if (HIWORD(*pFlags) == NDR_LOCAL_DATA_REPRESENTATION)
        return wine_dbg_sprintf("MAKELONG(%s, NDR_LOCAL_DATA_REPRESENTATION)", loword);
    else
        return wine_dbg_sprintf("MAKELONG(%s, 0x%04x)", loword, HIWORD(*pFlags));
}