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
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _tcsnicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ chop_blank (int /*<<< orphan*/ **) ; 
 int txt_clr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
WORD str_to_color(LPTSTR* arg_str)
{
    LPTSTR str;
    BOOL bBri;

    WORD tmp_clr,ret_clr;

    str = *arg_str;

    if (!(*str))
        return (WORD)-1;

    /* foreground */
    bBri = FALSE;

    if (_tcsnicmp(str,_T("bri"),3) == 0)
    {
        bBri = TRUE;

        if (chop_blank(&str))
            return (WORD)-1;
    }

    if ((tmp_clr = txt_clr(str)) == (WORD)-1)
    {
        return (WORD)-1;
    }

    /* skip spaces and "on" keyword */
    if (chop_blank(&str) || chop_blank(&str))
        return (WORD)-1;

    ret_clr = tmp_clr | (bBri << 3);

    /* background */
    bBri = FALSE;

    if (_tcsnicmp(str,_T("bri"),3) == 0 )
    {
        bBri = TRUE;

        if (chop_blank(&str))
            return (WORD)-1;
    }

    if ( (tmp_clr = txt_clr(str)) == (WORD)-1 )
        return (WORD)-1;

    chop_blank(&str);

    *arg_str = str;

    /* NOTE: See the note on SC_HEX in the StringToColor()'s description */
    return /* SC_HEX | */ ret_clr | tmp_clr << 4 | bBri << 7;
}