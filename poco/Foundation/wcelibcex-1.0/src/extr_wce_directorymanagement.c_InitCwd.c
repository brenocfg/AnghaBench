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

/* Variables and functions */
 scalar_t__* Cwd ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetModuleFileName (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MAX_PATH ; 
 int errno ; 
 scalar_t__* wcsrchr (scalar_t__*,char) ; 

__attribute__((used)) static int InitCwd()
{
    if( Cwd[0] )
        return 0;
    if( !GetModuleFileName( NULL, Cwd, _MAX_PATH ) )
        return errno = GetLastError();
    else
    {
        wchar_t* slash = wcsrchr( Cwd, '\\' );
        if( !slash )
            slash = wcsrchr( Cwd, '/' );
        if( slash )
        {
            if( slash == Cwd )
                slash++;
            *slash = 0;
        }
        return 0;
    }
}