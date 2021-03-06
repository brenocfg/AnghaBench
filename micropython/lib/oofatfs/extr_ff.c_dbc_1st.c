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
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 scalar_t__* DbcTbl ; 

__attribute__((used)) static int dbc_1st (BYTE c)
{
#if FF_CODE_PAGE == 0       /* Variable code page */
    if (DbcTbl && c >= DbcTbl[0]) {
        if (c <= DbcTbl[1]) return 1;                   /* 1st byte range 1 */
        if (c >= DbcTbl[2] && c <= DbcTbl[3]) return 1; /* 1st byte range 2 */
    }
#elif FF_CODE_PAGE >= 900   /* DBCS fixed code page */
    if (c >= DbcTbl[0]) {
        if (c <= DbcTbl[1]) return 1;
        if (c >= DbcTbl[2] && c <= DbcTbl[3]) return 1;
    }
#else                       /* SBCS fixed code page */
    if (c != 0) return 0;   /* Always false */
#endif
    return 0;
}