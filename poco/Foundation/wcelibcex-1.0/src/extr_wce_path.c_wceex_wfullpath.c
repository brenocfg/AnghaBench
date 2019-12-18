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
typedef  scalar_t__ wchar_t ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t wceex_GetFullPathNameW (scalar_t__ const*,size_t,scalar_t__*,scalar_t__**) ; 

wchar_t* wceex_wfullpath( wchar_t *absPath, const wchar_t *relPath, size_t maxLength )
{
    wchar_t* lpFilePart;
    DWORD ret = wceex_GetFullPathNameW( relPath, maxLength, absPath, &lpFilePart );
    if( !ret || ret > maxLength )
    {
        *absPath = 0;
        return NULL;
    }
    return absPath;
}