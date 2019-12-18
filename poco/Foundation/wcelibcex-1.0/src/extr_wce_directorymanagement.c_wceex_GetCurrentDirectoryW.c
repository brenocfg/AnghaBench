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
typedef  scalar_t__* LPWSTR ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  Cwd ; 
 scalar_t__ InitCwd () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  wcscpy (scalar_t__*,int /*<<< orphan*/ ) ; 
 size_t wcslen (int /*<<< orphan*/ ) ; 

DWORD wceex_GetCurrentDirectoryW( DWORD nBufferLength, LPWSTR lpBuffer )
{
    *lpBuffer = 0;
    if( InitCwd() )
    {
        SetLastError( errno );
        return 0;
    }
    else
    {
        size_t slen = wcslen( Cwd );
        if( slen >= (size_t)nBufferLength )
            return slen + 1;
        wcscpy( lpBuffer, Cwd );
        return slen;
    }
}