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
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  CP_BLANK_NOT_FOUND ; 
 int /*<<< orphan*/  CP_END_OF_STRING ; 
 int /*<<< orphan*/  CP_OK ; 
 scalar_t__ _T (char) ; 
 scalar_t__ _istspace (scalar_t__) ; 
 scalar_t__* _tcschr (scalar_t__*,scalar_t__) ; 

__attribute__((used)) static
INT chop_blank(LPTSTR *arg_str)
{
    LPTSTR str;
    str = _tcschr(*arg_str,_T(' '));
    if (!str)
    {
        str = _tcschr (*arg_str, _T('\0'));
        if (str != NULL)
            *arg_str=str;
        return CP_BLANK_NOT_FOUND;
    }

    while(_istspace(*str))
        str++;

    if (*str == _T('\0'))
    {
        *arg_str=str;
        return CP_END_OF_STRING;
    }

    *arg_str = str;

    return CP_OK;
}