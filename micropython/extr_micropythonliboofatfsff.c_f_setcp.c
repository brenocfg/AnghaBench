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
typedef  int WORD ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  FRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int CodePage ; 
#define  Ct437 147 
#define  Ct720 146 
#define  Ct737 145 
#define  Ct771 144 
#define  Ct775 143 
#define  Ct850 142 
#define  Ct852 141 
#define  Ct857 140 
#define  Ct860 139 
#define  Ct861 138 
#define  Ct862 137 
#define  Ct863 136 
#define  Ct864 135 
#define  Ct865 134 
#define  Ct866 133 
#define  Ct869 132 
 int /*<<< orphan*/ * DbcTbl ; 
#define  Dc932 131 
#define  Dc936 130 
#define  Dc949 129 
#define  Dc950 128 
 int /*<<< orphan*/ * ExCvt ; 
 int /*<<< orphan*/  FR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FR_OK ; 

FRESULT f_setcp (
    WORD cp     /* Value to be set as active code page */
)
{
    static const WORD       validcp[] = {  437,   720,   737,   771,   775,   850,   852,   857,   860,   861,   862,   863,   864,   865,   866,   869,   932,   936,   949,   950, 0};
    static const BYTE* const tables[] = {Ct437, Ct720, Ct737, Ct771, Ct775, Ct850, Ct852, Ct857, Ct860, Ct861, Ct862, Ct863, Ct864, Ct865, Ct866, Ct869, Dc932, Dc936, Dc949, Dc950, 0};
    UINT i;


    for (i = 0; validcp[i] != 0 && validcp[i] != cp; i++) ; /* Find the code page */
    if (validcp[i] != cp) return FR_INVALID_PARAMETER;  /* Not found? */

    CodePage = cp;
    if (cp >= 900) {    /* DBCS */
        ExCvt = 0;
        DbcTbl = tables[i];
    } else {            /* SBCS */
        ExCvt = tables[i];
        DbcTbl = 0;
    }
    return FR_OK;
}