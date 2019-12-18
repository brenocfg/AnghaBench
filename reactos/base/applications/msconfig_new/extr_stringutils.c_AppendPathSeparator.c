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

/* Variables and functions */
 size_t MAX_PATH ; 
 scalar_t__ _T (char) ; 
 size_t _tcslen (scalar_t__*) ; 

LPTSTR AppendPathSeparator(LPTSTR lpszPath)
{
    size_t iLen = 0;

    if (!lpszPath || (iLen = _tcslen(lpszPath)) >= MAX_PATH)
        return NULL;

    if (iLen >= 1)
    {
        lpszPath += iLen - 1;
        if (*lpszPath++ != _T('\\'))
        {
            *lpszPath++ = _T('\\');
            *lpszPath   = _T('\0');
        }
    }

    return lpszPath;
}