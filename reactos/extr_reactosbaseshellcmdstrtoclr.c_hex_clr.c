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
typedef  scalar_t__ TCHAR ;
typedef  scalar_t__* LPTSTR ;

/* Variables and functions */
 scalar_t__ _T (char) ; 
 scalar_t__ _istdigit (scalar_t__) ; 
 scalar_t__ _totupper (scalar_t__) ; 

__attribute__((used)) static
WORD hex_clr(LPTSTR str)
{
    WORD ret= (WORD)-1;
    TCHAR ch;

    ch = str[1];

    if (_istdigit(ch))
        ret = ch-_T('0');
    else
    {
        ch=_totupper(ch);

        if (  ch >= _T('A') && ch <= _T('F')  )
            ret = ch-_T('A')+10;
        else
            return (WORD)-1;
    }

    ch = str[0];

    if (_istdigit(ch))
        ret |= (ch-_T('0')) << 4;
    else
    {
        ch=_totupper(ch);

        if (  ch >= _T('A') && ch <= _T('F')  )
            ret |= (ch-_T('A')+10) <<4;
        else
            return (WORD)-1;
    }

    return ret;
}