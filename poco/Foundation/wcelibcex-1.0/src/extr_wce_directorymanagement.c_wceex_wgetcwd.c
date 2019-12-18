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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ wceex_GetCurrentDirectoryW (int,int /*<<< orphan*/ *) ; 

wchar_t* wceex_wgetcwd( wchar_t *buffer, int maxlen )
{
    if( !buffer && (buffer = (wchar_t*)malloc(maxlen * sizeof(wchar_t))) == NULL )
    {
        errno = ENOMEM;
        return NULL;
    }
    else
    {
        DWORD slen = wceex_GetCurrentDirectoryW( maxlen, buffer );
        if( !slen )
            return NULL;
        if( slen >= (DWORD)maxlen )
        {
            errno = ERANGE;
            return NULL;
        }
        return buffer;
    }
}