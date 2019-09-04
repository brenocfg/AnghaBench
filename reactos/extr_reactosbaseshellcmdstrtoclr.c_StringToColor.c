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
typedef  scalar_t__ WORD ;
typedef  scalar_t__* LPWORD ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  chop_blank (int /*<<< orphan*/ *) ; 
 scalar_t__ hex_clr (int /*<<< orphan*/ ) ; 
 scalar_t__ str_to_color (int /*<<< orphan*/ *) ; 

BOOL StringToColor(LPWORD lpColor, LPTSTR*str)
{
    WORD wRet;

    wRet = str_to_color (str);
    if (wRet == (WORD)-1)
    {
        wRet=hex_clr (*str);
        chop_blank (str);
        if (wRet == (WORD)-1)
            return FALSE;
    }

    *lpColor = wRet;

    return TRUE;
}